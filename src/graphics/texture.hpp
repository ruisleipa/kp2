#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>
#include <iostream>
#include <cstdlib>
#include <set>
#include <tr1/memory>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/glew.h>

#include "vector2d.hpp"
#include "preparedtexture.hpp"

class Texture
{
	public:		
		void bind();
		
		void draw(Vector2D position,Vector2D size);
		void drawClipped(Vector2D position,Vector2D size,Vector2D clip_position,Vector2D clip_size);		
		
		void setFilter(TextureFilter filter);
		TextureFilter getFilter();
		
		void reuploadTexture();
		
		Vector2D getSize();
		
		Texture();
		Texture(const std::string& filename);
		Texture(SDL_Surface* surface);

	private:
		void loadFromFile(const std::string& filename);
		void loadFromSurface(SDL_Surface* surface);

		std::tr1::shared_ptr<PreparedTexture> preparedTexture;
};

#endif // TEXTURE_HPP
