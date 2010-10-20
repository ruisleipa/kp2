#include "image.hpp"

#include "utils/string.hpp"
#include "debug/assert.hpp"
#include "graphics/color.hpp"
#include "graphics/window.hpp"

#include <GL/gl.h>

void Image::setTexture(const Texture& texture)
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

void Image::onDraw(DrawEvent event)
{
	Vector2D imageSize;
	
	if(!stretched)
	{
		imageSize=texture.getSize();
		imageSize.setX(imageSize.getX());
		
		// ratio>1 = wide, ratio<1=tall 
		float imageRatio=imageSize.getX()/imageSize.getY();
		
		Vector2D dest=event.getAreaSize();
	
		// ratio>1 = wide, ratio<1=tall 
		float dest_ratio=dest.getX()/dest.getY();
	
		if(fill)
		{			
			if(imageRatio>dest_ratio)
			{
				//image is wider than dest
				imageSize*=dest.getY()/imageSize.getY();			
			}
			else
			{
				//image is taller than dest
				imageSize*=dest.getX()/imageSize.getX();	
			}
		}
		else
		{
			if(imageRatio<dest_ratio)
			{
				//image is wider than dest
				imageSize*=dest.getY()/imageSize.getY();			
			}
			else
			{
				//image is taller than dest
				imageSize*=dest.getX()/imageSize.getX();	
			}
		}
	}
	else
	{
		imageSize=event.getAreaSize();
	}
	
	color.apply();
	
	texture.draw(event.getAreaPosition(),imageSize);
}

Image::Image():
	texture(),
	stretched(false),
	fill(false),
	color(1,1,1)
{

}

