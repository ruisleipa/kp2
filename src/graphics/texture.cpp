#include "texture.hpp"

#include "shared/string.hpp"
#include "assert.hpp"
#include <iostream>
#include <stdint.h>

std::set<Texture*> Texture::m_textures;
TextureFilter Texture::m_filter_limit=LINEAR;

static void CheckGL()
{
	GLenum error=glGetError();
		
	if(error != GL_NO_ERROR)
		std::cerr << "GL error: " << gluErrorString(error) << std::endl;
}

void Texture::init()
{
	m_filter=LINEAR;
	m_surface=0;	
	m_texture=0;	
	m_texture_width=0;
	m_texture_height=0;
	m_image_width=0;
	m_image_height=0;
}

Texture::Texture()
{
	Texture::addManagedTexture(this);

	init();
}

Texture::Texture(const std::string& filename)
{
	Texture::addManagedTexture(this);

	init();
	load(filename);
}

Texture::~Texture()
{
	Texture::removeManagedTexture(this);

	free();	
}

void Texture::copy(const Texture& b)
{
	init();

	m_texture_width=b.m_texture_width;
	m_texture_height=b.m_texture_height;

	if(b.m_surface)
	{
		m_surface=SDL_CreateRGBSurface(SDL_SWSURFACE,b.m_surface->w,b.m_surface->h,32,RGBAMASK);

		if(SDL_MUSTLOCK(m_surface))
			SDL_LockSurface(m_surface);
		if(SDL_MUSTLOCK(b.m_surface))
			SDL_LockSurface(b.m_surface);

		memcpy(m_surface->pixels,b.m_surface->pixels,4*b.m_surface->h*b.m_surface->w);

		if(SDL_MUSTLOCK(m_surface))
			SDL_UnlockSurface(m_surface);
		if(SDL_MUSTLOCK(b.m_surface))
			SDL_UnlockSurface(b.m_surface);
	}

	m_filter=b.m_filter;
	m_image_width=b.m_image_width;
	m_image_height=b.m_image_height;
	m_tag=b.m_tag;
	createTexture();
	setFilter(m_filter);
}

Texture::Texture(const Texture& b)
{
	Texture::addManagedTexture(this);

	copy(b);
}

Texture& Texture::operator=(const Texture& b)
{
	if(this!=&b)
	{
		copy(b);
	}

	return *this;
}

void Texture::free()
{
	deleteTexture();
	freeSurface();
	init();
}

void Texture::freeSurface()
{
	if(m_surface)
	{
		SDL_FreeSurface(m_surface);	
		m_surface=0;
		m_tag="";
	}
}

void Texture::draw(Vector2D position,Vector2D size)
{
	float iw=m_image_width;
	float ih=m_image_height;
	float tw=m_texture_width;
	float th=m_texture_height;
	
	bind();
	
	glBegin(GL_QUADS);
	
		glTexCoord2f(0, -(1));
		glVertex2d(position.getX(),position.getY());
		glTexCoord2f(iw/tw, -(1));
		glVertex2d(position.getX()+size.getX(),position.getY());	
		glTexCoord2f(iw/tw, -(1.0-ih/th));
		glVertex2d(position.getX()+size.getX(),position.getY()+size.getY());
		glTexCoord2f(0, -(1.0-ih/th));
		glVertex2d(position.getX(),position.getY()+size.getY());
	
	glEnd();
}

void Texture::drawClipped(Vector2D position,Vector2D size,Vector2D clip_position,Vector2D clip_size)
{
	float sx=clip_position.getX();
	float sy=clip_position.getY();
	float ex=clip_position.getX()+clip_size.getX();
	float ey=clip_position.getY()+clip_size.getY();
	
	float iw=m_image_width;
	float ih=m_image_height;
	float tw=m_texture_width;
	float th=m_texture_height;
	
	bind();
	
	glBegin(GL_QUADS);
	
		glTexCoord2f(sx/tw,-(1.0-sy/th));
		glVertex2d(position.getX(),position.getY());		
		glTexCoord2f(ex/tw,-(1.0-sy/th));
		glVertex2d(position.getX()+size.getX(),position.getY());		
		glTexCoord2f(ex/tw,-(1.0-ey/th));
		glVertex2d(position.getX()+size.getX(),position.getY()+size.getY());		
		glTexCoord2f(sx/tw,-(1.0-ey/th));
		glVertex2d(position.getX(),position.getY()+size.getY());
	
	glEnd();
}

static unsigned int powerOfTwo(unsigned int n)
{
	unsigned int i=1;
	while(i<n)
		i<<=1;

	return i;
}

void Texture::setFilter(TextureFilter filter)
{
	m_filter=filter;
	
	if(filter>m_filter_limit)
		filter=m_filter_limit;
	
	if(!m_texture)
		return;

	GLint min;
	GLint max;

	switch(filter)
	{
		default:
		case NEAREST:
			max=GL_NEAREST;
			min=GL_NEAREST;
			break;

		case LINEAR:
			max=GL_LINEAR;
			min=GL_LINEAR;
			break;

		case TRILINEAR:
			max=GL_LINEAR;
			min=GL_LINEAR_MIPMAP_LINEAR;
			break;
	}

	bind();

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,max);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,min);

	CheckGL();
}

void Texture::reuploadTexture()
{
	m_texture=0;
	createTexture();
}

TextureFilter Texture::getFilter()
{
	return m_filter;
}

int Texture::loadSurface(SDL_Surface* surface)
{
	loadSurface(surface,convertToString(surface));
}

int Texture::loadSurface(SDL_Surface* surface,const std::string& tag)
{
	if(!surface)
		return -1;
	
	if(!(surface->w && surface->h))
		return -1;	
		
	free();
	
	m_tag=tag;
		
	m_image_width=surface->w;
	m_image_height=surface->h;
	m_texture_width=powerOfTwo(surface->w);
	m_texture_height=powerOfTwo(surface->h);
	
	m_surface=SDL_CreateRGBSurface(SDL_SWSURFACE,m_texture_width,m_texture_height,32,RGBAMASK);
	SDL_SetAlpha(m_surface, 0,SDL_ALPHA_OPAQUE);
	SDL_SetAlpha(surface,0,SDL_ALPHA_OPAQUE);	
	
	SDL_BlitSurface(surface,0,m_surface,0);
	
	int max_tex_size;
	
	glGetIntegerv(GL_MAX_TEXTURE_SIZE,&max_tex_size);
		
	int bigside=std::max(m_texture_width,m_texture_height);
	int downscalefactor=0;
	
	while(bigside > max_tex_size)
	{
		bigside = bigside >> 1;
		downscalefactor++;
	}	
	
	if(downscalefactor)
	{
		SDL_Surface* tmpsurface=downScale(m_surface,downscalefactor);
		SDL_FreeSurface(m_surface);
		m_surface=tmpsurface;
	}
	
	if(SDL_MUSTLOCK(m_surface))
		SDL_LockSurface(m_surface);
		
	uint32_t* px=(uint32_t*)m_surface->pixels;
	
	if(m_image_width != m_surface->h)
	{
		for(int x=0; x<m_surface->w; x++)
		{
			px[(m_surface->h-1)*m_surface->w+x]=px[x];
		}
	}
	
	/*if(m_image_width != m_surface->w)
	{
		for(int y=0; y<m_surface->h; y++)
		{
			px[y*m_surface->w+m_surface->w-1]=px[y*m_surface->w];
		}
	}
	
	if((m_image_width != m_surface->w) || (m_image_width != m_surface->h))
	{
		px[m_surface->h*m_surface->w-1]=px[0];
	}*/
	
	if(SDL_MUSTLOCK(m_surface))
		SDL_UnlockSurface(m_surface);	

	createTexture();

	return 0;	
}

int Texture::load(const std::string& filename)
{
	SDL_Surface* image=IMG_Load(filename.c_str());
	
	if(!image)
	{
		std::cout<<"failed to load file "<<filename<<std::endl;
		return 0;
	}
	
	int ret=loadSurface(image,filename);	
	
	SDL_FreeSurface(image);
		
	return ret;
}


Vector2D Texture::getSize()
{
	return Vector2D(m_image_width,m_image_height);	
}

struct Pixel
{
	uint8_t v[4];
};

inline uint32_t divide(uint32_t a,uint32_t b,uint32_t c,uint32_t d)
{
	uint8_t p[4]={0,0,0,0};
	
	for(int i=0;i<4;i++)
	{
		p[i]+=(a&0xff)>>2;
		a>>=8;
		p[i]+=(b&0xff)>>2;
		b>>=8;
		p[i]+=(c&0xff)>>2;
		c>>=8;
		p[i]+=(d&0xff)>>2;
		d>>=8;
	}

	return p[0] | p[1]<<8 | p[2]<<16 | p[3]<<24;
}

SDL_Surface* Texture::downScale(SDL_Surface* surface,int factor)
{
	assert(surface != 0);
	
	if(!surface)
	{
		return 0;
	}

	if(SDL_MUSTLOCK(surface))
		SDL_LockSurface(surface);
		
	uint32_t* px=(uint32_t*)surface->pixels;
	
	int cw=surface->w;
	int ch=surface->h;
	int w=surface->w;
	int h=surface->h;
	int row=surface->w*4;
	
	uint32_t a;
	uint32_t b;
	uint32_t c;
	uint32_t d;
	
	while(factor--)
	{	
		if(cw > 1 && ch > 1)
		{
			cw = cw / 2;
			ch = ch / 2;
		
			for(int y=0;y<ch;y++)
			{	
				for(int x=0;x<cw;x++)
				{
					a=px[(x*2)+(y*2)*w];
					b=px[(x*2)+(y*2)*w+1];
					c=px[(x*2)+(y*2+1)*w];
					d=px[(x*2)+(y*2+1)*w+1];
					
					px[x+y*w]=divide(a,b,c,d);
					px[x+y*w]=px[x+y*w];
				}
			}
		}
		else if(cw > 1 && ch == 1)
		{
			cw = cw / 2;
		
			int y=0;
			
			for(int x=0;x<cw;x++)
			{
				a=px[(x*2)+(y)*w];
				b=px[(x*2)+(y)*w+1];
				c=px[(x*2)+(y+1)*w];
				d=px[(x*2)+(y+1)*w+1];
				
				px[x+y*w]=divide(a,b,c,d);
				px[x+y*w]=px[x+y*w];
			}			
		}
		else if(cw == 1 && ch > 1)
		{
			ch = ch / 2;
			
			int x=0;
		
			for(int y=0;y<ch;y++)
			{	
				a=px[(x)+(y*2)*w];
				b=px[(x)+(y*2)*w+1];
				c=px[(x)+(y*2+1)*w];
				d=px[(x)+(y*2+1)*w+1];
					
				px[x+y*w]=divide(a,b,c,d);
				px[x+y*w]=px[x+y*w];
			}
		}
		else if(cw == 1 && ch == 1)
		{
			break;
		}		
	}

	if(SDL_MUSTLOCK(surface))
		SDL_UnlockSurface(surface);
		
	SDL_Surface* newsurface=SDL_CreateRGBSurface(SDL_SWSURFACE,cw,ch,32,RGBAMASK);
	SDL_Rect size;
	size.x = 0;
	size.y = 0;
	size.w = cw;
	size.h = ch;
	
	SDL_BlitSurface(surface,&size,newsurface,0);
	
	return newsurface;
}

int Texture::createTexture()
{
	deleteTexture();
	
	glGenTextures(1,&m_texture);
		
	if(!m_surface)
	{
		return -1;
	}

	bind();
	glPixelStorei(GL_UNPACK_ALIGNMENT,4);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

	if(SDL_MUSTLOCK(m_surface))
		SDL_LockSurface(m_surface);

	gluBuild2DMipmaps(GL_TEXTURE_2D,GL_RGBA,m_surface->w,m_surface->h,GL_RGBA,GL_UNSIGNED_BYTE,m_surface->pixels);

	if(SDL_MUSTLOCK(m_surface))
		SDL_UnlockSurface(m_surface);

	setFilter(m_filter);
	
	CheckGL();
	
	return 0;
}

void Texture::deleteTexture()
{
	if(!m_texture)
		return;

	glDeleteTextures(1,&m_texture);
	m_texture=0;
}

void Texture::bind()
{
	GLint texture;
	
	glGetIntegerv(GL_TEXTURE_BINDING_2D,&texture);
	
	if(m_texture == texture)
		return;

	glBindTexture(GL_TEXTURE_2D,m_texture);

	CheckGL();
}

GLuint Texture::getTexture()
{
	return m_texture;
}

void Texture::setFilterLimit(TextureFilter filter)
{
	m_filter_limit=filter;
	
	std::set<Texture*>::iterator i;
		
	for(i=Texture::m_textures.begin();i!=Texture::m_textures.end();++i)
	{
		(*i)->setFilter((*i)->getFilter());
	}
}

TextureFilter Texture::getFilterLimit()
{
	return m_filter_limit;
}

void Texture::addManagedTexture(Texture* texture)
{
	if(texture)
		Texture::m_textures.insert(texture);
}

void Texture::removeManagedTexture(Texture* texture)
{
	Texture::m_textures.erase(texture);
}

void Texture::reuploadTextures()
{
#ifdef WIN32
	std::set<Texture*>::iterator i;
		
	for(i=Texture::m_textures.begin();i!=Texture::m_textures.end();++i)
	{
		(*i)->reuploadTexture();
	}
#endif
}

void Texture::printTextureList()
{
	std::set<Texture*>::iterator i;
	
	size_t totalsize=0;
	
	for(i=Texture::m_textures.begin();i!=Texture::m_textures.end();++i)
	{
		totalsize+=(*i)->printInfo();
	}
	
	std::string unit="B";	
	
	if(totalsize>1023)
	{
		totalsize/=1024;
		unit="kB";
	}
	
	if(totalsize>1023)
	{
		totalsize/=1024;
		unit="MB";
	}
	
	std::cout<<"---Textures---"<<std::endl;
	std::cout<<"Total texture size: "<<totalsize<<" "<<unit<<std::endl;
}

int Texture::printInfo()
{
	if(!m_surface)
		return 0;
	
	int size=(m_surface->w*m_surface->h*4);
	std::string unit="B";	
	
	if(size>1023)
	{
		size/=1024;
		unit="kB";
	}
	
	if(size>1023)
	{
		size/=1024;
		unit="MB";
	}
	
	std::cout << "---Texture---" << std::endl;
	std::cout << "Tag: " << m_tag << std::endl;
	std::cout << "Size: " << size << " "<< unit << std::endl;
	std::cout << "Dimensions: " << m_surface->w << "x" << m_surface->h  << std::endl;

	return m_surface->w*m_surface->h*4;
}

