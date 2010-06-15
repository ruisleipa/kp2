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
	
	glBindTexture(GL_TEXTURE_2D,m_texture);
	
	glBegin(GL_QUADS);
	
		glTexCoord2f(0, 1);
		glVertex2d(position.getX(),position.getY());
		glTexCoord2f(1, 1);
		glVertex2d(position.getX()+size.getX(),position.getY());	
		glTexCoord2f(1, 0);
		glVertex2d(position.getX()+size.getX(),position.getY()+size.getY());
		glTexCoord2f(0, 0);
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
	
	glBindTexture(GL_TEXTURE_2D,m_texture);
	
	glBegin(GL_QUADS);
	
		glTexCoord2f(sx/iw,1.0-sy/ih);
		glVertex2d(position.getX(),position.getY());		
		glTexCoord2f(ex/iw,1.0-sy/ih);
		glVertex2d(position.getX()+size.getX(),position.getY());		
		glTexCoord2f(ex/iw,1.0-ey/ih);
		glVertex2d(position.getX()+size.getX(),position.getY()+size.getY());		
		glTexCoord2f(sx/iw,1.0-ey/ih);
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
	
	m_surface=SDL_CreateRGBSurface(SDL_SWSURFACE,surface->w,surface->h,32,RGBAMASK);
	SDL_SetAlpha(m_surface, 0,SDL_ALPHA_OPAQUE);
	SDL_SetAlpha(surface,0,SDL_ALPHA_OPAQUE);
	
	SDL_BlitSurface(surface,0,m_surface,0);	
	
	int max_tex_size;
	
	int w=m_texture_width;
	int h=m_texture_height;
	
	glGetIntegerv(GL_MAX_TEXTURE_SIZE,&max_tex_size);
	
	if(w > max_tex_size)
		w = max_tex_size;

	if(h > max_tex_size)
		h = max_tex_size;

	SDL_Surface* tmpsurface=scaleAndFlip(m_surface,w,h);
	SDL_FreeSurface(m_surface);
	m_surface=tmpsurface;

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

struct Pixel
{
	uint8_t v[4];
};

SDL_Surface* Texture::scaleAndFlip(SDL_Surface* surface,int w,int h)
{
	SDL_Surface* dstsurface=SDL_CreateRGBSurface(SDL_SWSURFACE,w,h,32,RGBAMASK);

	if(!dstsurface)
		return 0;

	if(SDL_MUSTLOCK(surface))
		SDL_LockSurface(surface);

	if(SDL_MUSTLOCK(dstsurface))
		SDL_LockSurface(dstsurface);

	Pixel* src=(Pixel*)surface->pixels;
	Pixel* dst=(Pixel*)dstsurface->pixels;
	
	/*
	These are the steps that are made in the source surface per pixel in the
	destination surface.
	*/
	float xstep=float(surface->w)/float(w);
	float ystep=float(surface->h)/float(h);
	
	float src_x=0;
	float src_y=0;
	
	float xratio=0;
	float yratio=0;
	float xratioinv=0;
	float yratioinv=0;
	
	int offset;
	int dstoffset=(h-1)*w;
	
	Pixel avg[2];
	Pixel* pixels[4];
	
	for(int dst_y=0;dst_y<h;dst_y++)
	{	
		offset=int(src_y)*surface->w;
	
		/*
		For some reason	that I don't fully understand these ratios are
		"upside down". I guess it may have something to do with the
		flipping.
		*/
		yratioinv=src_y-int(src_y);
		yratio=1.0-yratioinv;
		
		src_x=0;
	
		for(int dst_x=0;dst_x<w;dst_x++)
		{
			/*
			For some reason	that I don't fully understand these ratios are
			"upside down". I guess it may have something to do with the
			flipping.
			*/
		
			xratioinv=src_x-int(src_x);
			xratio=1.0-xratioinv;
			
			pixels[0]=&src[offset + int(src_x)];
			pixels[1]=&src[offset + int(src_x+1)];
			pixels[2]=&src[offset + surface->w + int(src_x)];
			pixels[3]=&src[offset + surface->w + int(src_x+1)];
		
			avg[0].v[0]=pixels[0]->v[0]*xratio + pixels[1]->v[0]*xratioinv;
			avg[0].v[1]=pixels[0]->v[1]*xratio + pixels[1]->v[1]*xratioinv;
			avg[0].v[2]=pixels[0]->v[2]*xratio + pixels[1]->v[2]*xratioinv;
			avg[0].v[3]=pixels[0]->v[3]*xratio + pixels[1]->v[3]*xratioinv;
			
			avg[1].v[0]=pixels[2]->v[0]*xratio + pixels[3]->v[0]*xratioinv;
			avg[1].v[1]=pixels[2]->v[1]*xratio + pixels[3]->v[1]*xratioinv;
			avg[1].v[2]=pixels[2]->v[2]*xratio + pixels[3]->v[2]*xratioinv;
			avg[1].v[3]=pixels[2]->v[3]*xratio + pixels[3]->v[3]*xratioinv;
		
			dst[dstoffset+dst_x].v[0]=avg[0].v[0]*yratio + avg[1].v[0]*yratioinv;
			dst[dstoffset+dst_x].v[1]=avg[0].v[1]*yratio + avg[1].v[1]*yratioinv;
			dst[dstoffset+dst_x].v[2]=avg[0].v[2]*yratio + avg[1].v[2]*yratioinv;
			dst[dstoffset+dst_x].v[3]=avg[0].v[3]*yratio + avg[1].v[3]*yratioinv;
			
			src_x+=xstep;
			
			if(src_x>surface->w-1)
				src_x=surface->w-1;
		}
		
		src_y+=ystep;
		dstoffset-=w;
		
		if(src_y>surface->h-2)
			src_y=surface->h-2;
	}
	
	if(SDL_MUSTLOCK(surface))
		SDL_UnlockSurface(surface);
	
	if(SDL_MUSTLOCK(dstsurface))
		SDL_UnlockSurface(dstsurface);

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
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);

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

