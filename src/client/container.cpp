#include "container.hpp"

#include "assert.hpp"
#include "graphics.hpp"
#include "scissor.hpp"
#include "color.hpp"
#include "widget.hpp"
#include "keyevent.hpp"
#include "mouseevent.hpp"
#include "shared/string.hpp"

#include <iostream>

#include <GL/gl.h>
#include <SDL/SDL.h>

void Container::keyDown(KeyEvent event)
{
	if(m_focused)
		m_focused->keyDown(event);
}

void Container::keyUp(KeyEvent event)
{
	if(m_focused)
		m_focused->keyUp(event);
}

void Container::mouseDown(MouseEvent event)
{
	Widget* widget=findWidgetUnderPoint(event.getPosition());
	
	if(widget != m_focused)
	{
		if(m_focused)
			m_focused->blur();
	
		m_focused=widget;
		
		if(m_focused)
			m_focused->focus();
	}
	
	if(widget)
		widget->mouseDown(event);
}

void Container::mouseUp(MouseEvent event)
{
	Widget* widget=findWidgetUnderPoint(event.getPosition());

	if(widget)
		widget->mouseUp(event);
}

void Container::mouseMove(MouseEvent event)
{
	Widget* widget=findWidgetUnderPoint(event.getPosition());
	
	if(widget != m_mouse_over)
	{
		if(m_mouse_over)
			m_mouse_over->mouseOut();
	
		m_mouse_over=widget;
		
		if(m_mouse_over)
			m_mouse_over->mouseOn();
	}
	
	if(m_mouse_over)
		m_mouse_over->mouseMove(event);
}

void Container::resize(Graphics& graphics)
{
	std::vector<TaggedWidget>::iterator i;
	
	for(i=m_widgets.begin();i!=m_widgets.end();++i)
	{
		Widget* widget=(*i).m_widget;
	
		widget->resize(graphics);
	}	
}

void Container::draw(Graphics& graphics)
{
	std::vector<TaggedWidget>::iterator i;
	
	Scissor scissor(graphics);
	
	for(i=m_widgets.begin();i!=m_widgets.end();++i)
	{
		Widget* widget=(*i).m_widget;
	
		if(!widget->getVisible())
			continue;
	
		scissor.set(widget->getPosition(),widget->getSize());
		
		/*	
		Vector2D begin=(*i)->getPosition();
		Vector2D end=begin+(*i)->getSize();
	
		glBindTexture(GL_TEXTURE_2D,0);
		
		if((*i)==m_focused)		
			Color(1,0,0).apply();
		else
			Color(0,1,0).apply();

		glBegin(GL_QUADS);
			glVertex2f(begin.getX(),begin.getY());
			glVertex2f(end.getX(),	begin.getY());
			glVertex2f(end.getX(),	end.getY());
			glVertex2f(begin.getX(),end.getY());
		glEnd();
		*/	
	
		widget->draw(graphics);
	}
	
	scissor.reset();
}

void Container::addWidget(Widget* widget)
{
	assert(widget != 0);
	
	if(widget)
	{
		addWidget(convertToString(widget),widget);
	}
}

void Container::addWidget(std::string tag,Widget* widget)
{
	assert(widget != 0);
	
	if(widget)
	{
		TaggedWidget tagged_widget;
		
		tagged_widget.m_tag=tag;
		tagged_widget.m_widget=widget;		
	
		m_widgets.push_back(tagged_widget);
		widget->setParent(this);
	}
}

Widget* Container::getWidget(std::string tag)
{
	std::vector<TaggedWidget>::iterator i;
	
	for(i=m_widgets.begin();i!=m_widgets.end();++i)
	{
		if(tag==(*i).m_tag)
			return (*i).m_widget;	
	}

	return 0;	
}

void Container::calculateLayout()
{

}

void Container::onActivate()
{

}

Container::Container():
	m_mouse_over(0),
	m_focused(0)
{

}

Widget* Container::findWidgetUnderPoint(Vector2D point)
{
	std::vector<TaggedWidget>::reverse_iterator i;
	
	for(i=m_widgets.rbegin();i!=m_widgets.rend();++i)
	{
		Widget* widget=(*i).m_widget;

		if(!widget->getVisible())
			continue;
	
		Vector2D begin=widget->getPosition();
		Vector2D end=(widget->getPosition()+widget->getSize());
		
		bool y=point.getY()>=begin.getY() && point.getY()<=end.getY();
		bool x=point.getX()>=begin.getX() && point.getX()<=end.getX();
		
		if(x && y)
			return widget;
	}
	
	return 0;
}

