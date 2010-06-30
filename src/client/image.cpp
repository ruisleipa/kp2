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

void Image::setFill(bool fill)
{
	m_fill=fill;
}

bool Image::getFill()
{
	return m_fill;
}

void Image::setColor(Color color)
{
	m_color=color;
}

Color Image::getColor()
{
	return m_color;
}

void Image::onDraw(Graphics& graphics)
{
	if(!m_texture)
		return;
	
	Vector2D image_size;
	
	if(!m_stretched)
	{
		image_size=m_texture->getSize();
		image_size.setX(image_size.getX()/graphics.getAspectRatio());
		
		// ratio>1 = wide, ratio<1=tall 
		float image_ratio=image_size.getX()/image_size.getY();
		
		Vector2D dest=getSize();
	
		// ratio>1 = wide, ratio<1=tall 
		float dest_ratio=dest.getX()/dest.getY();
	
		if(m_fill)
		{			
			if(image_ratio>dest_ratio)
			{
				//image is wider than dest
				image_size*=dest.getY()/image_size.getY();			
			}
			else
			{
				//image is taller than dest
				image_size*=dest.getX()/image_size.getX();	
			}
		}
		else
		{
			if(image_ratio<dest_ratio)
			{
				//image is wider than dest
				image_size*=dest.getY()/image_size.getY();			
			}
			else
			{
				//image is taller than dest
				image_size*=dest.getX()/image_size.getX();	
			}
		}
	}
	else
	{
		image_size=getSize();
	}
	
	m_color.apply();
	
	m_texture->draw(getScreenPosition(),image_size);
}

Image::Image():
	m_texture(0),
	m_stretched(false),
	m_fill(false),
	m_color(1,1,1)
{

}

