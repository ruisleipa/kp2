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

	Widget* widget=findWidgetUnderMouse(event);
	
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

	Widget* widget=findWidgetUnderMouse(event);

	if(widget)
		widget->mouseUp(event);
}

void Container::mouseMove(MouseEvent event)
{
	Widget::mouseMove(event);
	
	Widget* widget=findWidgetUnderMouse(event);
	
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

void Container::draw(DrawEvent event)
{
	Widget::draw(event);
	
	std::vector<Widget*>::iterator i;
	
	Scissor scissor(event.getWindow());
	
	scissor.reset();
	
	for(i=children.begin();i!=children.end();++i)
	{
		Widget* widget=(*i);
	
		if(!widget->getVisible())
			continue;
	
		Vector2D start = event.getAreaPosition();
		
		if(widget->hasPixelPosition())
			start += widget->getPosition();
		else
			start += widget->getPosition() * event.getAreaSize();
		
		Vector2D size;
		
		if(widget->hasPixelSize())
			size = widget->getSize();
		else
			size = widget->getSize() * event.getAreaSize();
				
#if 1
		scissor.reset();
	
		Vector2D begin=start;
		Vector2D end=begin+size;
	
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
		scissor.set(start,size);
	
		EventArea eventArea(event.getWindow(), start, size);
		DrawEvent drawEvent(eventArea);
	
		widget->draw(drawEvent);
	}
	
	scissor.reset();
}

void Container::showOnlyWidget(const std::string& tag)
{
	std::vector<Widget*>::iterator i;
	
	for(i=children.begin(); i!=children.end(); ++i)
	{
		(*i)->setVisible(false);
	}
	
	if(tags.find(tag) != tags.end())
	{
		tags[tag]->setVisible(true);
	}
}

void Container::addWidget(Widget& child)
{
	children.push_back(&child);
	
	child.setParent(this);
}

void Container::addWidget(const std::string& tag,Widget& child)
{
	tags[tag]=&child;
	
	addWidget(child);
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
	focusedChild(0),
	mouseOverChild(0)
{

}

Widget* Container::findWidgetUnderMouse(MouseEvent event)
{
	std::vector<Widget*>::reverse_iterator i;
	
	for(i = children.rbegin(); i != children.rend(); ++i)
	{
		Widget* widget = (*i);

		if(!widget->getVisible())
			continue;
	
		Vector2D begin = event.getAreaPosition();
		
		if(widget->hasPixelPosition())
			begin += widget->getPosition();
		else
			begin += widget->getPosition() * event.getAreaSize();
		
		Vector2D size;
		
		if(widget->hasPixelSize())
			size = widget->getSize();
		else
			size = widget->getSize() * event.getAreaSize();
		
		Vector2D end = begin + size;
		
		Vector2D point = event.getMousePosition();
		
		bool y = point.getY() >= begin.getY() && point.getY() <= end.getY();
		bool x = point.getX() >= begin.getX() && point.getX() <= end.getX();
		
		if(x && y)
			return widget;
	}
	
	return 0;
}

