#include "image.hpp"

#include "shared/string.hpp"
#include "assert.hpp"
#include "color.hpp"
#include "graphics.hpp"

#include <GL/gl.h>

void Image::setTexture(Texture* texture)
{
	m_texture=texture;
}

Texture* Image::getTexture()
{
	return m_texture;
}

void Image::setStretched(bool stretched)
{
	m_stretched=stretched;
}

bool Image::getStrecthed()
{
	return m_stretched;
}

void Image::draw(Graphics& graphics)
{
	if(!m_texture)
		return;
	
	Vector2D image_size;
	
	if(!m_stretched)
	{
		image_size=m_texture->getSize();
		image_size.setX(image_size.getX()/graphics.getAspectRatio());
		Vector2D size=getSize();
	
		float ratio;
	
		if(image_size.getY() > image_size.getX())
		{
			ratio=size.getX()/image_size.getX();
		}
		else
		{
			ratio=size.getY()/image_size.getY();
		}
		
		image_size*=ratio;
	}
	else
	{
		image_size=getSize();
	}
	
	Color(1,1,1).apply();
	
	m_texture->draw(getPosition(),image_size);
}

Image::Image()
{
	m_texture=0;
	m_stretched=false;
}

