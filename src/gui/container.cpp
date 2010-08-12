#include "container.hpp"

#include "debug/assert.hpp"

#include "graphics/window.hpp"
#include "graphics/scissor.hpp"
#include "graphics/color.hpp"
#include "graphics/texture.hpp"

#include "events/keyevent.hpp"
#include "events/mouseevent.hpp"
#include "utils/string.hpp"

#include <stdexcept>
#include <sstream>

#include <GL/gl.h>
#include <SDL/SDL.h>

void Container::doKeyDown(KeyEvent event)
{
	Widget::doKeyDown(event);

	if(m_focused)
		m_focused->doKeyDown(event);
}

void Container::doKeyUp(KeyEvent event)
{
	Widget::doKeyUp(event);

	if(m_focused)
		m_focused->doKeyUp(event);
}

void Container::doMouseDown(MouseEvent event)
{
	Widget::doMouseDown(event);

	Widget* widget=findWidgetUnderPoint(event.getPosition());
	
	if(widget != m_focused)
	{
		if(m_focused)
			m_focused->doBlur();
	
		m_focused=widget;
		
		if(m_focused)
			m_focused->doFocus();
	}
	
	if(widget)
		widget->doMouseDown(event);

}

void Container::doMouseUp(MouseEvent event)
{
	Widget::doMouseUp(event);

	Widget* widget=findWidgetUnderPoint(event.getPosition());

	if(widget)
		widget->doMouseUp(event);
}

void Container::doMouseMove(MouseEvent event)
{
	Widget::doMouseMove(event);
	
	Widget* widget=findWidgetUnderPoint(event.getPosition());
	
	if(widget != m_mouse_over)
	{
		if(m_mouse_over)
			m_mouse_over->doMouseOut();
	
		m_mouse_over=widget;
		
		if(m_mouse_over)
			m_mouse_over->doMouseOn();
	}
	
	if(m_mouse_over)
		m_mouse_over->doMouseMove(event);
}

void Container::doResize(Window& window)
{
	Widget::doResize(window);

	std::vector<TaggedWidget>::iterator i;
	
	for(i=m_widgets.begin();i!=m_widgets.end();++i)
	{
		Widget* widget=(*i).m_widget;
	
		widget->doResize(window);
	}	
}

void Container::doDraw(Window& window)
{
	Widget::doDraw(window);
	
	std::vector<TaggedWidget>::iterator i;
	
	Scissor scissor(window);
	
	for(i=m_widgets.begin();i!=m_widgets.end();++i)
	{
		Widget* widget=(*i).m_widget;
	
		if(!widget->getVisible())
			continue;
	
		Vector2D start=getScreenPosition()+widget->getPosition();
#if 0
		scissor.reset();
	
		Vector2D begin=start;
		Vector2D end=begin+widget->getSize();
	
		Texture().bind();
		
		if(widget==m_focused)		
			Color(1,0,0,1).apply();
		else
			Color(0,1,0,1).apply();

		glBegin(GL_LINE_LOOP);
			glVertex2f(begin.getX(),begin.getY());
			glVertex2f(end.getX(),	begin.getY());
			glVertex2f(end.getX(),	end.getY());
			glVertex2f(begin.getX(),end.getY());
		glEnd();
#endif
		scissor.set(start,widget->getSize());
	
		widget->doDraw(window);
	}
	
	scissor.reset();
}

void Container::addWidget(Widget* widget)
{
	if(widget)
	{
		addWidget(convertToString(widget),widget);
	}
}

void Container::addWidget(std::string tag,Widget* widget)
{
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

int Container::getWidgetCount()
{
	return m_widgets.size();
}

Widget* Container::getWidget(int index)
{
	if(index < 0 && index >= m_widgets.size())
	{
		std::stringstream ss;
		
		ss << "getWidget failed: invalid index ";
		ss << index;
	
		throw std::runtime_error(ss.str());
	}
	
	return m_widgets[index].m_widget;
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
	
		Vector2D begin=getScreenPosition()+widget->getPosition();
		Vector2D end=begin+widget->getSize();
		
		bool y=point.getY()>=begin.getY() && point.getY()<=end.getY();
		bool x=point.getX()>=begin.getX() && point.getX()<=end.getX();
		
		if(x && y)
			return widget;
	}
	
	return 0;
}

