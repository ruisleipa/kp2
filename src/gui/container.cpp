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

void Container::keyDown(KeyEvent event)
{
	Widget::keyDown(event);

	if(focusedChild)
		focusedChild->keyDown(event);
}

void Container::keyUp(KeyEvent event)
{
	Widget::keyUp(event);

	if(focusedChild)
		focusedChild->keyUp(event);
}

void Container::mouseDown(MouseEvent event)
{
	Widget::mouseDown(event);

	Widget* widget=findWidgetUnderPoint(event.getPosition());
	
	if(widget != focusedChild)
	{
		if(focusedChild)
			focusedChild->blur();
	
		focusedChild=widget;
		
		if(focusedChild)
			focusedChild->focus();
	}
	
	if(widget)
		widget->mouseDown(event);

}

void Container::mouseUp(MouseEvent event)
{
	Widget::mouseUp(event);

	Widget* widget=findWidgetUnderPoint(event.getPosition());

	if(widget)
		widget->mouseUp(event);
}

void Container::mouseMove(MouseEvent event)
{
	Widget::mouseMove(event);
	
	Widget* widget=findWidgetUnderPoint(event.getPosition());
	
	if(widget != mouseOverChild)
	{
		if(mouseOverChild)
			mouseOverChild->mouseOut();
	
		mouseOverChild=widget;
		
		if(mouseOverChild)
			mouseOverChild->mouseOn();
	}
	
	if(mouseOverChild)
		mouseOverChild->mouseMove(event);
}

void Container::resize(Window& window)
{
	Widget::resize(window);

	std::vector<Widget*>::iterator i;
	
	for(i=children.begin();i!=children.end();++i)
	{
		Widget* widget=(*i);
	
		widget->resize(window);
	}	
}

void Container::draw(Window& window)
{
	Widget::draw(window);
	
	std::vector<Widget*>::iterator i;
	
	Scissor scissor(window);
	
	for(i=children.begin();i!=children.end();++i)
	{
		Widget* widget=(*i);
	
		if(!widget->getVisible())
			continue;
	
		Vector2D start=getAbsolutePosition()+widget->getPosition();
#if 0
		scissor.reset();
	
		Vector2D begin=start;
		Vector2D end=begin+widget->getSize();
	
		Texture().bind();
		
		if(widget==focusedChild)		
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
	
		widget->draw(window);
	}
	
	scissor.reset();
}

void Container::addChild(Widget& child)
{
	children.push_back(&child);
	
	child.setParent(this);
}

int Container::getChildCount()
{
	return children.size();
}

Widget* Container::getChild(int index)
{
	if(index < 0 && index >= children.size())
	{
		std::stringstream ss;
		
		ss << "getChild failed: invalid index '" << index << "'";

		throw std::runtime_error(ss.str());
	}
	
	return children[index];
}

Container::Container():
	mouseOverChild(0),
	focusedChild(0)
{

}

Widget* Container::findWidgetUnderPoint(Vector2D point)
{
	std::vector<Widget*>::reverse_iterator i;
	
	for(i=children.rbegin();i!=children.rend();++i)
	{
		Widget* widget=(*i);

		if(!widget->getVisible())
			continue;
	
		Vector2D begin=getAbsolutePosition()+widget->getPosition();
		Vector2D end=begin+widget->getSize();
		
		bool y=point.getY()>=begin.getY() && point.getY()<=end.getY();
		bool x=point.getX()>=begin.getX() && point.getX()<=end.getX();
		
		if(x && y)
			return widget;
	}
	
	return 0;
}

