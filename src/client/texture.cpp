#include "texture.hpp"

#include "shared/string.hpp"

std::set<Texture*> Texture::m_textures;
TextureFilter Texture::m_filter_limit;

static void CheckGL()
{
	GLenum errflag;
	bool errors = false;
	while ((errflag = glGetError()) != GL_NO_ERROR)
	{
		errors = true;
		std::cerr << "GL error: " << gluErrorString(errflag) << "\n";
	}
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

		memcpy(m_surface->pixels,b.m_surface->pixels,4*m_texture_height*m_texture_width);

		if(SDL_MUSTLOCK(m_surface))
			SDL_UnlockSurface(m_surface);
		if(SDL_MUSTLOCK(b.m_surface))
			SDL_UnlockSurface(b.m_surface);
	}

	m_filter=b.m_filter;
	m_image_width=b.m_image_width;
	m_image_height=b.m_image_height;
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
	
	glBindTexture(GL_TEXTURE_2D,m_texture);
	
	glBegin(GL_QUADS);
	
		glTexCoord2f(0, 1);
		glVertex2d(position.getX(),position.getY());
		glTexCoord2f(iw/tw, 1);
		glVertex2d(position.getX()+size.getX(),position.getY());	
		glTexCoord2f(iw/tw, 1.0-ih/th);
		glVertex2d(position.getX()+size.getX(),position.getY()+size.getY());
		glTexCoord2f(0, 1.0-ih/th);
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
	
	glBindTexture(GL_TEXTURE_2D,m_texture);
	
	glBegin(GL_QUADS);
	
		glTexCoord2f(sx/tw,1.0-sy/th);
		glVertex2d(position.getX(),position.getY());		
		glTexCoord2f(ex/tw,1.0-sy/th);
		glVertex2d(position.getX()+size.getX(),position.getY());		
		glTexCoord2f(ex/tw,1.0-ey/th);
		glVertex2d(position.getX()+size.getX(),position.getY()+size.getY());		
		glTexCoord2f(sx/tw,1.0-ey/th);
		glVertex2d(position.getX(),position.getY()+size.getY());
	
	glEnd();
	
	glPopMatrix();
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

	glBindTexture(GL_TEXTURE_2D,m_texture);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,max);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,min);

	CheckGL();
}

void Texture::reuploadTexture()
{
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
	
	int size=(m_texture_width*m_texture_height*4);
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
	
	std::cout<<"Surface: \""<<m_tag<<"\" "<<m_texture_width<<"x"<<m_texture_height<<" size: "<<size<<" "<<unit<<std::endl;
	
	m_surface=SDL_CreateRGBSurface(SDL_SWSURFACE,m_texture_width,m_texture_height,32,RGBAMASK);
	SDL_SetAlpha(m_surface, 0,SDL_ALPHA_OPAQUE);
	SDL_SetAlpha(surface,0,SDL_ALPHA_OPAQUE);
	
	SDL_BlitSurface(surface,0,m_surface,0);	

	if(!m_surface)
	{
		std::cout<<"failed to copy and convert image data "<<std::endl;
		return -1;
	}

	int max_tex_size;
	int x_ratio=1;
	int y_ratio=1;

	glGetIntegerv(GL_MAX_TEXTURE_SIZE,&max_tex_size);

	x_ratio=m_texture_width/max_tex_size;
	y_ratio=m_texture_height/max_tex_size;

	if(x_ratio<1)
		x_ratio=1;
	if(y_ratio<1)
		y_ratio=1;

	m_surface=downScale(m_surface,x_ratio,y_ratio);

	if(!m_surface)
	{
		std::cerr<<"cannot allocate a surface for scaling"<<std::endl;	
		return -1;
	}

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

SDL_Surface* Texture::downScale(SDL_Surface* surface,int x_ratio,int y_ratio)
{
	int dstwidth=surface->w/x_ratio;
	int dstheight=surface->h/y_ratio;
	SDL_Surface* dstsurface=SDL_CreateRGBSurface(SDL_SWSURFACE,dstwidth,dstheight,32,RGBAMASK);

	if(!dstsurface)
		return 0;

	if(SDL_MUSTLOCK(surface))
		SDL_LockSurface(surface);

	if(SDL_MUSTLOCK(dstsurface))
		SDL_LockSurface(dstsurface);

	uint32_t* src=(uint32_t*)surface->pixels;
	uint32_t* dst=(uint32_t*)dstsurface->pixels;

	int dst_offset=dstwidth*(dstheight-1);
	int src_offset=0;
	int src_x=0;
	int pixel_area=x_ratio*y_ratio;	//amount of pixels in the area where the average of one
				//pixel iis calculated from

	for(int y=0;y<dstheight;y++)
	{
		src_x=0;

		for(int x=0;x<dstwidth;x++)
		{
			//We scale the image by averaging xratio*yratio pixels from the source image 
			//for each pixel in the destination image
			
			//We calculate average of every color component on their own. We dont need 
			//worry about endianness.
			int bytes[4]={0,0,0,0};

			//collect the pixel values from source bitmap
			int soff=src_offset+src_x; 	// Offset to the first pixel of the area in the
							// source bitmap
			
			for(int sy=0;sy<y_ratio;sy++)
			{
				for(int sx=0;sx<x_ratio;sx++)
				{
					uint32_t pixel=0;
					pixel=src[soff+sx];

					bytes[0]+=pixel&0xFF;	
					pixel=pixel>>8;
					bytes[1]+=pixel&0xFF;	
					pixel=pixel>>8;
					bytes[2]+=pixel&0xFF;	
					pixel=pixel>>8;
					bytes[3]+=pixel&0xFF;	
				}

				soff+=surface->w;
			}

			bytes[0]/=pixel_area;	
			bytes[1]/=pixel_area;	
			bytes[2]/=pixel_area;	
			bytes[3]/=pixel_area;	
			
			uint32_t pixel=0;
			pixel=pixel|(bytes[3]&0xFF);
			pixel=pixel<<8;
			pixel=pixel|(bytes[2]&0xFF);
			pixel=pixel<<8;
			pixel=pixel|(bytes[1]&0xFF);
			pixel=pixel<<8;
			pixel=pixel|(bytes[0]&0xFF);
		
			dst[dst_offset+x]=pixel;	

			src_x+=x_ratio;
		}

		dst_offset-=dstwidth;
		src_offset+=surface->w*y_ratio;
	}
	
	if(SDL_MUSTLOCK(surface))
		SDL_UnlockSurface(surface);
	
	if(SDL_MUSTLOCK(dstsurface))
		SDL_UnlockSurface(dstsurface);

	SDL_FreeSurface(surface);
	return dstsurface;

}

int Texture::createTexture()
{
	deleteTexture();
	
	glGenTextures(1,&m_texture);
		
	if(!m_surface)
	{
		return -1;
	}

	glBindTexture(GL_TEXTURE_2D,m_texture);
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

GLuint Texture::getTexture()
{
	return m_texture;
}

void Texture::setFilterLimit(TextureFilter filter)
{
	m_filter_limit=filter;
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
	std::set<Texture*>::iterator i;
		
	for(i=Texture::m_textures.begin();i!=Texture::m_textures.end();++i)
	{
		(*i)->reuploadTexture();
	}
}

