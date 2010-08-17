#include "image.hpp"

#include "utils/string.hpp"
#include "debug/assert.hpp"
#include "graphics/color.hpp"
#include "graphics/window.hpp"

#include <GL/gl.h>

void Image::setTexture(Texture& texture)
{
	this->texture=texture;
}

Texture& Image::getTexture()
{
	return texture;
}

void Image::setStretched(bool stretched)
{
	this->stretched=stretched;
}

bool Image::getStrecthed()
{
	return stretched;
}

void Image::setFill(bool fill)
{
	this->fill=fill;
}

bool Image::getFill()
{
	return fill;
}

void Image::setColor(Color color)
{
	this->color=color;
}

Color Image::getColor()
{
	return color;
}

void Image::onDraw(Window& window)
{
	Vector2D image_size;
	
	if(!stretched)
	{
		image_size=texture.getSize();
		image_size.setX(image_size.getX()/window.getAspectRatio());
		
		// ratio>1 = wide, ratio<1=tall 
		float image_ratio=image_size.getX()/image_size.getY();
		
		Vector2D dest=getSize();
	
		// ratio>1 = wide, ratio<1=tall 
		float dest_ratio=dest.getX()/dest.getY();
	
		if(fill)
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
	
	color.apply();
	
	texture.draw(getAbsolutePosition(),image_size);
}

Image::Image():
	texture(),
	stretched(false),
	fill(false),
	color(1,1,1)
{

}

