#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>
#include <iostream>
#include <cstdlib>
#include <set>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/glew.h>

#include "vector2d.hpp"
#include "texturecollection.hpp"

#include "utils/noncopyable.hpp"

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

class Texture: public NonCopyable
{
	public:		
		void bind();
		
		void draw(Vector2D position,Vector2D size);
		void drawClipped(Vector2D position,Vector2D size,Vector2D clip_position,Vector2D clip_size);		
		
		GLuint getTexture();
		
		void setFilter(TextureFilter filter);
		TextureFilter getFilter();
		
		void reuploadTexture();
		
		Vector2D getSize();
		
		Texture();
		Texture(const std::string& filename);
		Texture(SDL_Surface* surface);
		~Texture();

	private:
		void loadFromFile(const std::string& filename);
		void loadFromSurface(SDL_Surface* surface);
		void freeTextureData();
		
		void createTexture();		
		void deleteTexture();
	
		void init();

		SDL_Surface* downScale(int factor);			

		TextureFilter filter;
		GLuint texture;
		SDL_Surface* textureData;
		int imageWidth;
		int imageHeight;
		int textureWidth;
		int textureHeight;
		
};

#endif // TEXTURE_HPP
