#include "texture.hpp"

#include "utils/string.hpp"
#include "debug/assert.hpp"

#include <iostream>
#include <stdexcept>
#include <stdint.h>

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

void Texture::reuploadTexture()
{
	if(preparedTexture.get())
		preparedTexture->upload();
}

void Texture::loadFromFile(const std::string& filename)
{
	SDL_Surface* image=IMG_Load(filename.c_str());
	
	if(!image)
	{
		std::string error;
		
		error += "Unable to load image: '";
		error += filename;
		error += "'";
		
		throw std::runtime_error(error);
	}
	
	loadFromSurface(image);	
	
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

