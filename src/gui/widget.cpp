#include "widget.hpp"

#include <stdexcept>

#include <GL/glew.h>

#include "graphics/texture.hpp"

void Widget::setPosition(Vector2D position)
{
	setFactorPosition(position);
}

void Widget::setFactorPosition(Vector2D position)
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
	setFactorSize(size);
}

void Widget::setFactorSize(Vector2D size)
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

void Widget::setFluid(bool fluid)
{
	this->fluid = fluid;
}

bool Widget::getFluid()
{
	return fluid;
}

void Widget::setVisible(bool visible)
{
	this->visible=visible;
	
	if(this->visible)
	{
		ShowEvent showEvent;
		handleEvent(&showEvent);
	}
	else
	{
		HideEvent hideEvent;
		handleEvent(&hideEvent);
	}
}	

bool Widget::getVisible()
{
	return visible;
}

void Widget::setBackgroundColor(const Color& color)
{
	backgroundColor = color;
}

const Color& Widget::getBackgroundColor()
{
	return backgroundColor;
}

void Widget::handleEvent(Event* event)
{
	if(dynamic_cast<DrawEvent*>(event))
		handleDrawEvent(dynamic_cast<DrawEvent*>(event));
}

void Widget::resize(Window& window)
{
	onResize(window);
}

void Widget::onResize(Window& window)
{
	
}

Widget::Widget():
	visible(true),
	parent(0),
	pixelPosition(true),
	pixelSize(true),
	fluid(false),
	backgroundColor(1,1,1,0)
{

}

Widget::~Widget()
{

}

void Widget::handleDrawEvent(DrawEvent* event)
{
	Vector2D begin=event->getAreaPosition();
	Vector2D end=begin+event->getAreaSize();

	Texture().bind();
	
	backgroundColor.apply();

	glBegin(GL_QUADS);
		glVertex2f(begin.getX(),begin.getY());
		glVertex2f(end.getX(),	begin.getY());
		glVertex2f(end.getX(),	end.getY());
		glVertex2f(begin.getX(),end.getY());
	glEnd();
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
