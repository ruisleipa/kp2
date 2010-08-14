#include "preparedtexture.hpp"

#include "utils/string.hpp"
#include "debug/assert.hpp"

#include <iostream>
#include <stdexcept>
#include <stdint.h>

void PreparedTexture::bind()
{
	GLint bindedTexture;
	
	glGetIntegerv(GL_TEXTURE_BINDING_2D,&bindedTexture);
	
	if(number == bindedTexture)
		return;

	glBindTexture(GL_TEXTURE_2D,number);

	checkOpenGlErrors();
}

void PreparedTexture::upload()
{
	deleteTexture();
	createTexture();
}

void PreparedTexture::setFilter(TextureFilter filter)
{
	if(!number)
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

	checkOpenGlErrors();
}

TextureFilter PreparedTexture::getFilter()
{
	return filter;
}

Vector2D PreparedTexture::getEndCoordinate()
{
	float x = float(width) / float(paddedWidth);
	float y = float(height) / float(paddedHeight);
	
	return Vector2D(x,y);	
}

Vector2D PreparedTexture::getSize()
{
	return Vector2D(width,height);	
}

void PreparedTexture::checkOpenGlErrors()
{
	GLenum error=glGetError();
		
	if(error != GL_NO_ERROR)
		std::cerr << "GL error: " << gluErrorString(error) << std::endl;
}

PreparedTexture::PreparedTexture(SDL_Surface* surface):
	filter(LINEAR),
	number(0),	
	data(0),	
	width(0),
	height(0),
	paddedWidth(0),
	paddedHeight(0)
{
	loadFromSurface(surface);
}

PreparedTexture::~PreparedTexture()
{
	deleteTexture();
	freeTextureData();
}

void PreparedTexture::freeTextureData()
{
	SDL_FreeSurface(data);
}

void PreparedTexture::loadFromSurface(SDL_Surface* surface)
{
	if(surface == 0)
		throw std::runtime_error("loadFromSurface: invalid surface passed");
	
	if(surface->w == 0 || surface->h == 0)
		throw std::runtime_error("loadFromSurface: invalid surface passed");
		
	width = surface->w;
	height = surface->h;
	
	calculatePaddedSize();
	createSurface();
	copySurface(surface);	
	downScaleSurface();
	createTexture();
}

void PreparedTexture::calculatePaddedSize()
{
	paddedWidth = getNextPowerOfTwo(width);
	paddedHeight = getNextPowerOfTwo(height);
}

void PreparedTexture::createSurface()
{
	data=SDL_CreateRGBSurface(SDL_SWSURFACE,paddedWidth,paddedHeight,32,RGBAMASK);
}

void PreparedTexture::copySurface(SDL_Surface* surface)
{
	SDL_SetAlpha(data,0,SDL_ALPHA_OPAQUE);
	SDL_SetAlpha(surface,0,SDL_ALPHA_OPAQUE);	
	SDL_BlitSurface(surface,0,data,0);
}

void PreparedTexture::downScaleSurface()
{
	int max_tex_size;
	
	glGetIntegerv(GL_MAX_TEXTURE_SIZE,&max_tex_size);
		
	int bigside=std::max(width,height);
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
}

unsigned int PreparedTexture::getNextPowerOfTwo(unsigned int number)
{
	unsigned int powerOfTwo=1;
	
	while(powerOfTwo < number)
		powerOfTwo <<= 1;

	return powerOfTwo;
}

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

SDL_Surface* PreparedTexture::downScale(int factor)
{
	if(SDL_MUSTLOCK(data))
		SDL_LockSurface(data);
		
	uint32_t* px=(uint32_t*)data->pixels;
	
	int cw=data->w;
	int ch=data->h;
	int w=data->w;
	int h=data->h;
	int row=data->w*4;
	
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

	if(SDL_MUSTLOCK(data))
		SDL_UnlockSurface(data);
		
	SDL_Surface* newsurface=SDL_CreateRGBSurface(SDL_SWSURFACE,cw,ch,32,RGBAMASK);
		
	SDL_Rect size;
	size.x = 0;
	size.y = 0;
	size.w = cw;
	size.h = ch;
	
	SDL_BlitSurface(data,&size,newsurface,0);
	
	SDL_FreeSurface(data);
	
	data = newsurface;
}

void PreparedTexture::createTexture()
{
	deleteTexture();
	
	glGenTextures(1,&number);
		
	bind();
	glPixelStorei(GL_UNPACK_ALIGNMENT,4);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

	if(SDL_MUSTLOCK(data))
		SDL_LockSurface(data);

	gluBuild2DMipmaps(GL_TEXTURE_2D,GL_RGBA,data->w,data->h,GL_RGBA,GL_UNSIGNED_BYTE,data->pixels);

	if(SDL_MUSTLOCK(data))
		SDL_UnlockSurface(data);

	setFilter(filter);
	
	checkOpenGlErrors();
}

void PreparedTexture::deleteTexture()
{
	if(glIsTexture(number))
		glDeleteTextures(1,&number);
}
