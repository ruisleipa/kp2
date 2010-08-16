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

	if(focusedChild)
		focusedChild->doKeyDown(event);
}

void Container::doKeyUp(KeyEvent event)
{
	Widget::doKeyUp(event);

	if(focusedChild)
		focusedChild->doKeyUp(event);
}

void Container::doMouseDown(MouseEvent event)
{
	Widget::doMouseDown(event);

	Widget* widget=findWidgetUnderPoint(event.getPosition());
	
	if(widget != focusedChild)
	{
		if(focusedChild)
			focusedChild->doBlur();
	
		focusedChild=widget;
		
		if(focusedChild)
			focusedChild->doFocus();
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
	
	if(widget != mouseOverChild)
	{
		if(mouseOverChild)
			mouseOverChild->doMouseOut();
	
		mouseOverChild=widget;
		
		if(mouseOverChild)
			mouseOverChild->doMouseOn();
	}
	
	if(mouseOverChild)
		mouseOverChild->doMouseMove(event);
}

void Container::doResize(Window& window)
{
	Widget::doResize(window);

	std::vector<TaggedWidget>::iterator i;
	
	for(i=children.begin();i!=children.end();++i)
	{
		Widget* widget=(*i).widget;
	
		widget->doResize(window);
	}	
}

void Container::doDraw(Window& window)
{
	Widget::doDraw(window);
	
	std::vector<TaggedWidget>::iterator i;
	
	Scissor scissor(window);
	
	for(i=children.begin();i!=children.end();++i)
	{
		Widget* widget=(*i).widget;
	
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
	
		widget->doDraw(window);
	}
	
	scissor.reset();
}



void Container::addChild(Widget& child)
{
	addChild(convertToString(&child),child);
}

void Container::addChild(std::string tag,Widget& child)
{
	TaggedWidget taggedWidget;
	
	taggedWidget.tag=tag;
	taggedWidget.widget=&child;		

	children.push_back(taggedWidget);
	
	child.setParent(this);
	child.setWindow(getWindow());
}

Widget* Container::getChild(std::string tag)
{
	std::vector<TaggedWidget>::iterator i;
	
	for(i=children.begin();i!=children.end();++i)
	{
		if(tag==(*i).tag)
			return (*i).widget;	
	}

	std::stringstream ss;
		
	ss << "getChild failed: invalid tag '" << tag << "'";

	throw Exception(ss.str());
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
	
	return children[index].widget;
}

void Container::setWindow(Window* window)
{
	Widget::setWindow(window);
	
	propagateWindowPointer();
}

void Container::propagateWindowPointer()
{	
	Window* window=getWindow();

	for(int i=0;i<getChildCount();i++)
	{
		getChild(i)->setWindow(window);
	}
}

Container::Container():
	mouseOverChild(0),
	focusedChild(0)
{

}

Widget* Container::findWidgetUnderPoint(Vector2D point)
{
	std::vector<TaggedWidget>::reverse_iterator i;
	
	for(i=children.rbegin();i!=children.rend();++i)
	{
		Widget* widget=(*i).widget;

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

