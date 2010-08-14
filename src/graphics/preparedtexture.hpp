#ifndef PREPAREDTEXTURE_HPP
#define PREPAREDTEXTURE_HPP

#include <iostream>
#include <cstdlib>

#include <SDL/SDL.h>
#include <GL/glew.h>

#include "vector2d.hpp"

#if SDL_BYTEORDER == SDL_BIG_ENDIAN

#define RMASK   0xff000000
#define GMASK   0x00ff0000
#define BMASK   0x0000ff00
#define AMASK   0x000000ff

#else

#define RMASK   0x000000ff
#define GMASK   0x0000ff00
#define BMASK   0x00ff0000
#define AMASK   0xff000000

#endif

#define RGBAMASK  RMASK,GMASK,BMASK,AMASK

enum TextureFilter {NEAREST,LINEAR,TRILINEAR};

class PreparedTexture
{
	public:		
		void bind();
		void upload();
		
		void setFilter(TextureFilter filter);
		TextureFilter getFilter();
		
		Vector2D getEndCoordinate();
				
		Vector2D getSize();
		
		PreparedTexture(SDL_Surface* surface);
		~PreparedTexture();

	private:		
		void loadFromSurface(SDL_Surface* surface);
		
		void calculatePaddedSize();
		void createSurface();
		void copySurface(SDL_Surface* surface);
		void downScaleSurface();
		
		void freeTextureData();
		
		void createTexture();		
		void deleteTexture();
		
		unsigned int getNextPowerOfTwo(unsigned int number);
		
		SDL_Surface* downScale(int factor);
			
		void checkOpenGlErrors();		
		
		TextureFilter filter;		
		GLuint number;		
		SDL_Surface* data;		
		int width;
		int height;
		int paddedWidth;
		int paddedHeight;
};

#endif // PREPAREDTEXTURE_HPP
