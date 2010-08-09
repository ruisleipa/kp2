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

class Texture
{
	public:
		int load(const std::string& filename);
		int loadSurface(SDL_Surface* surface);
		int loadSurface(SDL_Surface* surface,const std::string& tag);
		
		void bind();
		
		void draw(Vector2D position,Vector2D size);
		void drawClipped(Vector2D position,Vector2D size,Vector2D clip_position,Vector2D clip_size);		
		
		GLuint getTexture();
		
		void setFilter(TextureFilter filter);
		TextureFilter getFilter();
		
		static void setFilterLimit(TextureFilter filter);
		static TextureFilter getFilterLimit();
				
		int isEmpty();
		
		Vector2D getSize();
		
		static void reuploadTextures();	
		static void printTextureList();	
				
		Texture();
		Texture(const std::string& filename);
		Texture(const Texture&);
		Texture& operator=(const Texture&);
		~Texture();

	private:
		int createTexture();
		void deleteTexture();
		
		int printInfo();		
	
		void init();
		void copy(const Texture&);

		SDL_Surface* downScale(SDL_Surface* surface,int factor);

		std::string m_tag;

		//General stuff
		void free();	
		void freeSurface();	

		TextureFilter m_filter;

		SDL_Surface* m_surface;

		GLuint m_texture;

		int m_image_width;
		int m_image_height;
		int m_texture_width;
		int m_texture_height;
				
		static TextureFilter m_filter_limit;
		
		/*
		These are for texture reuploading in the case of OpenGl context
		loss on some platforms.
		*/		
		void reuploadTexture();
		
		static void addManagedTexture(Texture* texture);
		static void removeManagedTexture(Texture* texture);
		static std::set<Texture*> m_textures;

};

#endif // TEXTURE_HPP
