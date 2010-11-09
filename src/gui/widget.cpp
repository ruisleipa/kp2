#include "widget.hpp"

#include <stdexcept>

void Widget::setPosition(Vector2D position)
{
	pixelPosition=false;
	this->position=position;
}
	
void Widget::setPixelPosition(Vector2D position)
{
	pixelPosition=true;
	this->position=position;
}
	
Vector2D Widget::getPosition()
{
	return position;
}

void Widget::setSize(Vector2D size)
{
	pixelSize=false;
	this->size=size;
}
	
void Widget::setPixelSize(Vector2D size)
{
	pixelSize=true;
	this->size=size;
}
	
Vector2D Widget::getSize()
{
	return size;
}

void Widget::setVisible(bool visible)
{
	this->visible=visible;
	
	if(this->visible)
		onShow();
	else
		onHide();
}	

bool Widget::getVisible()
{
	return visible;
}

Widget::Widget():
	visible(true),
	parent(0),
	pixelPosition(true),
	pixelSize(true)
{

}

Widget::~Widget()
{

}

bool Widget::hasPixelPosition()
{
	return pixelPosition;
}

bool Widget::hasPixelSize()
{
	return pixelSize;
}

Container* Widget::getParent()
{
	return parent;
}

void Widget::setParent(Container* parent)
{
	this->parent=parent;
}
