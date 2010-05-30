#include "view.hpp"

#include "assert.hpp"
#include "graphics.hpp"
#include "scissor.hpp"
#include "color.hpp"

#include <iostream>

#include <GL/gl.h>
#include <SDL/SDL.h>

void View::keyDown(KeyEvent event)
{
	if(m_focused)
		m_focused->keyDown(event);
}

void View::keyUp(KeyEvent event)
{
	if(m_focused)
		m_focused->keyUp(event);
}

void View::mouseDown(MouseEvent event)
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

void View::mouseUp(MouseEvent event)
{
	Widget* widget=findWidgetUnderPoint(event.getPosition());

	if(widget)
		widget->mouseUp(event);
}

void View::mouseMove(MouseEvent event)
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

void View::draw()
{
	std::vector<Widget*>::iterator i;
	
	for(i=m_widgets.begin();i!=m_widgets.end();++i)
	{
		Scissor::set((*i)->getPosition(),(*i)->getSize());
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
	
		(*i)->draw();
	}
	
	Scissor::reset();
}

void View::addWidget(Widget* widget)
{
	assert(widget != 0);
	
	if(widget)
	{
		m_widgets.push_back(widget);
		widget->setParent(this);
	}
}

void View::calculateLayout()
{

}

void View::onActivate()
{

}

View::View()
{
	m_mouse_over=0;
	m_focused=0;
}

Widget* View::findWidgetUnderPoint(Vector2D point)
{
	std::vector<Widget*>::reverse_iterator i;
	
	Vector2D screen_size=Graphics::getInstance().getDisplaySize();
		
	for(i=m_widgets.rbegin();i!=m_widgets.rend();++i)
	{
		Widget* widget=(*i);
	
		Vector2D begin=widget->getPosition()*screen_size;
		Vector2D end=(widget->getPosition()+widget->getSize())*screen_size;
		
		bool y=point.getY()>=begin.getY() && point.getY()<=end.getY();
		bool x=point.getX()>=begin.getX() && point.getX()<=end.getX();
		
		if(x && y)
			return widget;
	}
	
	return 0;
}

