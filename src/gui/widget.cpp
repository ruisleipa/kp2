#include "widget.hpp"

#include <stdexcept>

#include <GL/glew.h>

#include "graphics/texture.hpp"

const std::string& Widget::getName()
{
	return name;
}

void Widget::setName(const std::string& name)
{
	this->name = name;
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

Vector2D Widget::getAutoSize()
{
	return Vector2D(0, 0);
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
		glVertex2f(begin.getX(), begin.getY());
		glVertex2f(end.getX(), begin.getY());
		glVertex2f(end.getX(), end.getY());
		glVertex2f(begin.getX(), end.getY());
	glEnd();
}
