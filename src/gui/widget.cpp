#include "widget.hpp"

#include <stdexcept>

#include <GL/glew.h>

#include "graphics/texture.hpp"
#include "utils/string.hpp"
#include "font.hpp"

const float TOOLTIP_TIME = 1.5;

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

Vector2D Widget::getLatestSize()
{
	return latestSize;
}

void Widget::setToolTip(std::string str)
{
	toolTip = str;
}

void Widget::handleEvent(Event* event)
{
	if(dynamic_cast<DrawEvent*>(event))
		handleDrawEvent(dynamic_cast<DrawEvent*>(event));
	if(dynamic_cast<MouseMoveEvent*>(event))
		handleMouseMoveEvent(dynamic_cast<MouseMoveEvent*>(event));
	if(dynamic_cast<MouseOutEvent*>(event))
		handleMouseOutEvent(dynamic_cast<MouseOutEvent*>(event));
}

Widget::Widget():
	visible(true),
	backgroundColor(1,1,1,0),
	mouseOn(false)
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
	
	if(mouseOn && toolTip != "" && toolTipTimer.getSeconds() > TOOLTIP_TIME)
	{
		glDisable(GL_SCISSOR_TEST);
		
		Font toolTipFont("tooltip");
		
		Vector2D toolTipSize = toolTipFont.getTextSize(convertToWideString(toolTip));
		
		const Vector2D margin(3, 3);
		
		Vector2D begin = mousePosition;
		Vector2D textBegin = mousePosition + margin;
		Vector2D end = begin + toolTipSize + margin * 2;
		
		Color(1, 1, 0.8).apply();
		
		glBegin(GL_QUADS);
			glVertex2f(begin.getX(), begin.getY());
			glVertex2f(end.getX(), begin.getY());
			glVertex2f(end.getX(), end.getY());
			glVertex2f(begin.getX(), end.getY());
		glEnd();
				
		Color(0, 0, 0).apply();
		
		glBegin(GL_LINE_LOOP);
			glVertex2f(begin.getX(), begin.getY());
			glVertex2f(end.getX(), begin.getY());
			glVertex2f(end.getX(), end.getY());
			glVertex2f(begin.getX(), end.getY());
		glEnd();
		
		toolTipFont.draw(convertToWideString(toolTip), textBegin);
		
		glEnable(GL_SCISSOR_TEST);
	}
		
	latestSize = event->getAreaSize();
}

void Widget::handleMouseMoveEvent(MouseMoveEvent* event)
{
	mouseOn = true;
	
	mousePosition = event->getAreaPosition() + event->getMousePosition();
	
	toolTipTimer.reset();
}

void Widget::handleMouseOutEvent(MouseOutEvent* event)
{
	mouseOn = false;
}
