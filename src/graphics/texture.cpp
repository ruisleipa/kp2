#include "texture.hpp"

#include "utils/string.hpp"
#include "debug/assert.hpp"

#include <iostream>
#include <stdexcept>
#include <stdint.h>

static void CheckGL()
{
	GLenum error=glGetError();
		
	if(error != GL_NO_ERROR)
		std::cerr << "GL error: " << gluErrorString(error) << std::endl;
}

void Texture::init()
{
	filter=LINEAR;
	textureData=0;	
	texture=0;	
	textureWidth=0;
	textureHeight=0;
	imageWidth=0;
	imageHeight=0;
}

Texture::Texture()
{
	init();
}

Texture::Texture(const std::string& filename)
{
	init();
	loadFromFile(filename);
}

Texture::Texture(SDL_Surface* surface)
{
	init();
	loadFromSurface(surface);
}

Texture::~Texture()
{
	deleteTexture();
	freeTextureData();
}

void Texture::freeTextureData()
{
	SDL_FreeSurface(textureData);
}

void Texture::draw(Vector2D position,Vector2D size)
{
	float iw=imageWidth;
	float ih=imageHeight;
	float tw=textureWidth;
	float th=textureHeight;
	
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
	
	float tw=textureWidth;
	float th=textureHeight;
	
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
	if(!texture)
		return;

	GLint min;
	GLint max;

	switch(this->filter)
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
	texture=0;
	createTexture();
}

TextureFilter Texture::getFilter()
{
	return filter;
}

void Texture::loadFromSurface(SDL_Surface* surface)
{
	if(surface == 0)
		throw std::runtime_error("loadFromSurface: invalid surface passed");
	
	if(surface->w == 0 || surface->h == 0)
		throw std::runtime_error("loadFromSurface: invalid surface passed");
		
	imageWidth=surface->w;
	imageHeight=surface->h;
	textureWidth=powerOfTwo(surface->w);
	textureHeight=powerOfTwo(surface->h);
	
	textureData=SDL_CreateRGBSurface(SDL_SWSURFACE,textureWidth,textureHeight,32,RGBAMASK);
	SDL_SetAlpha(textureData,0,SDL_ALPHA_OPAQUE);
	SDL_SetAlpha(surface,0,SDL_ALPHA_OPAQUE);	
	
	SDL_BlitSurface(surface,0,textureData,0);
	
	int max_tex_size;
	
	glGetIntegerv(GL_MAX_TEXTURE_SIZE,&max_tex_size);
		
	int bigside=std::max(textureWidth,textureHeight);
	int downscalefactor=0;
	
	while(bigside > max_tex_size)
	{
		bigside = bigside >> 1;
		downscalefactor++;
	}	
	
	if(downscalefactor)
	{
		downScale(downscalefactor);
	}
	
	createTexture();
}

void Texture::loadFromFile(const std::string& filename)
{
	SDL_Surface* image=IMG_Load(filename.c_str());
	
	if(!image)
	{
		std::cout<<"failed to load file "<<filename<<std::endl;
		return;
	}
	
	loadFromSurface(image);	
	
	SDL_FreeSurface(image);
}


Vector2D Texture::getSize()
{
	return Vector2D(imageWidth,imageHeight);	
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

SDL_Surface* Texture::downScale(int factor)
{
	if(SDL_MUSTLOCK(textureData))
		SDL_LockSurface(textureData);
		
	uint32_t* px=(uint32_t*)textureData->pixels;
	
	int cw=textureData->w;
	int ch=textureData->h;
	int w=textureData->w;
	int h=textureData->h;
	int row=textureData->w*4;
	
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

	if(SDL_MUSTLOCK(textureData))
		SDL_UnlockSurface(textureData);
		
	SDL_Surface* newsurface=SDL_CreateRGBSurface(SDL_SWSURFACE,cw,ch,32,RGBAMASK);
		
	SDL_Rect size;
	size.x = 0;
	size.y = 0;
	size.w = cw;
	size.h = ch;
	
	SDL_BlitSurface(textureData,&size,newsurface,0);
	
	SDL_FreeSurface(textureData);
	
	textureData = newsurface;
}

void Texture::createTexture()
{
	deleteTexture();
	
	glGenTextures(1,&texture);
		
	bind();
	glPixelStorei(GL_UNPACK_ALIGNMENT,4);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

	if(SDL_MUSTLOCK(surface))
		SDL_LockSurface(surface);

	gluBuild2DMipmaps(GL_TEXTURE_2D,GL_RGBA,surface->w,surface->h,GL_RGBA,GL_UNSIGNED_BYTE,surface->pixels);

	if(SDL_MUSTLOCK(surface))
		SDL_UnlockSurface(surface);

	setFilter(filter);
	
	CheckGL();
}

void Texture::deleteTexture()
{
	if(glIsTexture(texture))
		glDeleteTextures(1,&texture);
}

void Texture::bind()
{
	GLint bindedTexture;
	
	glGetIntegerv(GL_TEXTURE_BINDING_2D,&bindedTexture);
	
	if(texture == bindedTexture)
		return;

	glBindTexture(GL_TEXTURE_2D,texture);

	CheckGL();
}

GLuint Texture::getTexture()
{
	return texture;
}
