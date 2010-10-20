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
	{
		moveEventOrigin(event,focusedChild);
		focusedChild->keyDown(event);
	}
}

void Container::keyUp(KeyEvent event)
{
	Widget::keyUp(event);

	if(focusedChild)
	{
		moveEventOrigin(event,focusedChild);
		focusedChild->keyUp(event);
	}
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
	{
		moveEventOrigin(event,widget);
		widget->mouseDown(event);
	}
}

void Container::mouseUp(MouseEvent event)
{
	Widget::mouseUp(event);

	Widget* widget=findWidgetUnderMouse(event);

	if(widget)
	{
		moveEventOrigin(event,widget);
		widget->mouseUp(event);
	}
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
	{
		moveEventOrigin(event,mouseOverChild);	
		mouseOverChild->mouseMove(event);
	}
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
		
		DrawEvent drawEvent=event;
		
		moveEventOrigin(drawEvent,widget);
	
		scissor.set(drawEvent.getAreaPosition(),drawEvent.getAreaSize());
	
		widget->draw(drawEvent);
				
#if 1
		scissor.reset();
	
		Vector2D begin=drawEvent.getAreaPosition();
		Vector2D end=begin+drawEvent.getAreaSize();
	
		Texture().bind();
		
		if(widget==focusedChild)		
			Color(1,0,0).apply();
		else
			Color(0,1,0).apply();

		glBegin(GL_LINE_LOOP);
			glVertex2f(begin.getX(),begin.getY());
			glVertex2f(end.getX(),	begin.getY());
			glVertex2f(end.getX(),	end.getY());
			glVertex2f(begin.getX(),end.getY());
		glEnd();
#endif
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
	
		MouseEvent newEvent=event;
		
		moveEventOrigin(newEvent,widget);
		
		Vector2D size = newEvent.getAreaSize();
		
		Vector2D point = newEvent.getMousePosition();
		
		bool y = point.getY() >= 0 && point.getY() <= size.getY();
		bool x = point.getX() >= 0 && point.getX() <= size.getX();
		
		if(x && y)
			return widget;
	}
	
	return 0;
}

void Container::moveEventOrigin(Event& event,Widget* widget)
{
	event.moveOrigin(calculateWidgetPosition(widget,event.getAreaSize()));
	event.setAreaSize(calculateWidgetSize(widget,event.getAreaSize()));
}

Vector2D Container::calculateWidgetPosition(Widget* widget,Vector2D ourSize)
{
	if(widget->hasPixelPosition())
		return widget->getPosition();
	else
		return widget->getPosition() * ourSize;
}

Vector2D Container::calculateWidgetSize(Widget* widget,Vector2D ourSize)
{
	if(widget->hasPixelSize())
		return widget->getSize();
	else
		return widget->getSize() * ourSize;
}
