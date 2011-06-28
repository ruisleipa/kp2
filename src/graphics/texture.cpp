#include "texture.hpp"

#include "utils/string.hpp"
#include "debug/assert.hpp"

#include <iostream>
#include <stdexcept>
#include <stdint.h>

#include <SDL/SDL_image.h>
#include <GL/glew.h>

std::map<std::string, std::tr1::shared_ptr<PreparedTexture> > Texture::cache;

Texture::Texture()
{
	
}

Texture::Texture(const std::string& filename)
{
	loadFromFile(filename);
}

Texture::Texture(SDL_Surface* surface)
{
	loadFromSurface(surface);
}

void Texture::draw(Vector2D position,Vector2D size)
{
	if(!preparedTexture.get())
		return;
		
	Vector2D textureEnd = preparedTexture->getEndCoordinate();
	
	bind();
	
	glBegin(GL_QUADS);
	
		glTexCoord2f(0,-1);
		glVertex2d(position.getX(),position.getY());

		glTexCoord2f(textureEnd.getX(),-1);
		glVertex2d(position.getX()+size.getX(),position.getY());	

		glTexCoord2f(textureEnd.getX(),-(1.0-textureEnd.getY()));
		glVertex2d(position.getX()+size.getX(),position.getY()+size.getY());

		glTexCoord2f(0,-(1.0-textureEnd.getY()));
		glVertex2d(position.getX(),position.getY()+size.getY());
	
	glEnd();
}

void Texture::drawClipped(Vector2D position,Vector2D size,Vector2D clip_position,Vector2D clip_size)
{
	Vector2D clipBegin = clip_position / preparedTexture->getSize();
	Vector2D clipEnd = (clip_position + clip_size) / preparedTexture->getSize();
	
	clipBegin *= preparedTexture->getEndCoordinate();
	clipEnd *= preparedTexture->getEndCoordinate();
	
	bind();
	
	glBegin(GL_QUADS);
	
		glTexCoord2f(clipBegin.getX(),-(1.0-clipBegin.getY()));
		glVertex2d(position.getX(),position.getY());
		
		glTexCoord2f(clipEnd.getX(),-(1.0-clipBegin.getY()));
		glVertex2d(position.getX()+size.getX(),position.getY());		
		
		glTexCoord2f(clipEnd.getX(),-(1.0-clipEnd.getY()));
		glVertex2d(position.getX()+size.getX(),position.getY()+size.getY());		
		
		glTexCoord2f(clipBegin.getX(),-(1.0-clipEnd.getY()));
		glVertex2d(position.getX(),position.getY()+size.getY());
	
	glEnd();
}

void Texture::drawNineSliceScaled(Vector2D position,Vector2D size,Vector2D topleft, Vector2D bottomright)
{
	Vector2D textureSize = preparedTexture->getSize();
	int widths[3];
	int heights[3];
	int clipWidths[3];
	int clipHeights[3];
	int posX[3];
	int posY[3];
	
	widths[0] = topleft.getX();
	widths[1] = size.getX() - topleft.getX() - bottomright.getX();
	widths[2] = bottomright.getX();
	
	heights[0] = topleft.getY();
	heights[1] = size.getY()- topleft.getY() - bottomright.getY();
	heights[2] = bottomright.getY();
	
	clipWidths[0] = topleft.getX();
	clipWidths[1] = textureSize.getX() - topleft.getX() - bottomright.getX();
	clipWidths[2] = bottomright.getX();
	
	clipHeights[0] = topleft.getY();
	clipHeights[1] = textureSize.getY()- topleft.getY() - bottomright.getY();
	clipHeights[2] = bottomright.getY();
	
	posX[0] = position.getX();
	posX[1] = position.getX() + topleft.getX();
	posX[2] = position.getX() + size.getX() - bottomright.getX();
	
	posY[0] = position.getY();
	posY[1] = position.getY() + topleft.getY();
	posY[2] = position.getY() + size.getY() - bottomright.getY();

	Vector2D clipPosition;
	
	for(int y = 0; y < 3; ++y)
	{
		clipPosition.setX(0);
	
		for(int x = 0; x < 3; ++x)
		{		
			Vector2D clipSize = Vector2D(clipWidths[x], clipHeights[y]);
			Vector2D position = Vector2D(posX[x], posY[y]);
			Vector2D size = Vector2D(widths[x], heights[y]);
		
			drawClipped(position, size, clipPosition, clipSize);
			
			clipPosition += Vector2D(clipWidths[x], 0);
		}
		
		clipPosition += Vector2D(0, clipHeights[y]);
	}
}

void Texture::setFilter(TextureFilter filter)
{
	if(preparedTexture.get())
		preparedTexture->setFilter(filter);
}

TextureFilter Texture::getFilter()
{
	if(preparedTexture.get())
		return preparedTexture->getFilter();
	
	return NEAREST;
}

void Texture::upload()
{
	if(preparedTexture.get())
		preparedTexture->upload();
}

void Texture::free()
{
	if(preparedTexture.get())
		preparedTexture->free();
}

void Texture::loadFromFile(const std::string& filename)
{
	if(cache.find(filename) != cache.end())
	{
		preparedTexture = cache[filename];
		return;
	}
	
	SDL_Surface* image = IMG_Load(filename.c_str());
	
	if(!image)
	{
		std::string error;
		
		error += "Unable to load image: '";
		error += filename;
		error += "'";
		
		throw std::runtime_error(error);
	}
	
	loadFromSurface(image);
	
	cache[filename] = preparedTexture;
	
	SDL_FreeSurface(image);
}

void Texture::loadFromSurface(SDL_Surface* surface)
{
	preparedTexture.reset(new PreparedTexture(surface));
}

Vector2D Texture::getSize()
{
	if(preparedTexture.get())
		return preparedTexture->getSize();
	else
		return Vector2D(0,0);	
}

void Texture::bind()
{
	if(preparedTexture.get())
		preparedTexture->bind();
	else
		glBindTexture(GL_TEXTURE_2D,0);
}

