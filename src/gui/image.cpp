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

void Image::setScalingMode(Image::ScalingMode mode)
{
	scalingMode = mode;
}

void Image::setNineSliceCorners(Vector2D topLeft, Vector2D bottomRight)
{
	nineSliceTopLeft = topLeft;
	nineSliceBottomRight = bottomRight;
}

void Image::setColor(Color color)
{
	this->color=color;
}

Color Image::getColor()
{
	return color;
}

void Image::handleEvent(Event* event)
{
	Widget::handleEvent(event);

	if(dynamic_cast<DrawEvent*>(event))
		handleDrawEvent(dynamic_cast<DrawEvent*>(event));
}

void Image::handleDrawEvent(DrawEvent* event)
{
	color.apply();
	
	if(scalingMode == NONE)
	{
		texture.draw(event->getAreaPosition(), texture.getSize());
	}
	if(scalingMode == NINE_SLICE)
	{
		texture.drawNineSliceScaled(event->getAreaPosition(), event->getAreaSize(), nineSliceTopLeft, nineSliceBottomRight);
	}
	if(scalingMode == STRETCH_FILL)
	{
		texture.draw(event->getAreaPosition(), event->getAreaSize());
	}
	if(scalingMode == PROPORTIONAL || scalingMode == PROPORTIONAL_FILL)
	{
		bool fill;
		
		if(scalingMode == PROPORTIONAL)
			fill = false;
		else
			fill = true;
		
		Vector2D imageSize = texture.getSize();
		imageSize.setX(imageSize.getX());
		
		// ratio>1 = wide, ratio<1=tall 
		float imageRatio = imageSize.getX() / imageSize.getY();
		
		Vector2D dest = event->getAreaSize();
	
		// ratio>1 = wide, ratio<1=tall 
		float dest_ratio = dest.getX() / dest.getY();
	
		if(fill)
		{			
			if(imageRatio > dest_ratio)
			{
				//image is wider than dest
				imageSize *= dest.getY() / imageSize.getY();
			}
			else
			{
				//image is taller than dest
				imageSize *= dest.getX() / imageSize.getX();
			}
		}
		else
		{
			if(imageRatio < dest_ratio)
			{
				//image is wider than dest
				imageSize *= dest.getY() / imageSize.getY();
			}
			else
			{
				//image is taller than dest
				imageSize *= dest.getX() / imageSize.getX();
			}
		}
		
		texture.draw(event->getAreaPosition(),imageSize);
	}
}

Image::Image():
	texture(),
	scalingMode(PROPORTIONAL),
	color(1,1,1)
{

}

