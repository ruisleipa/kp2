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

void Container::handleEvent(Event* event)
{
	Widget::handleEvent(event);
	
	if(dynamic_cast<DrawEvent*>(event))
		handleDrawEvent(dynamic_cast<DrawEvent*>(event));	
	else if(dynamic_cast<KeyEvent*>(event))
		handleKeyEvent(dynamic_cast<KeyEvent*>(event));
	else if(dynamic_cast<MouseDownEvent*>(event))
		handleMouseDownEvent(dynamic_cast<MouseDownEvent*>(event));
	else if(dynamic_cast<MouseUpEvent*>(event))
		handleMouseUpEvent(dynamic_cast<MouseUpEvent*>(event));
	else if(dynamic_cast<MouseMoveEvent*>(event))
		handleMouseMoveEvent(dynamic_cast<MouseMoveEvent*>(event));
	else if(dynamic_cast<MouseOutEvent*>(event))
		handleMouseOutEvent(dynamic_cast<MouseOutEvent*>(event));
	else if(dynamic_cast<BlurEvent*>(event))
		handleBlurEvent(dynamic_cast<BlurEvent*>(event));
}

void Container::handleKeyEvent(KeyEvent* event)
{
	if(event->getKey() == SDLK_F5)
	{
		if(dynamic_cast<KeyDownEvent*>(event))
			showBounds = true;
		else if(dynamic_cast<KeyUpEvent*>(event))
			showBounds = false;
	}
		
	if(focusedChild)
	{
		convertAreaEventForChild(event,focusedChild);
		focusedChild->handleEvent(event);
	}
}

void Container::handleMouseDownEvent(MouseDownEvent* event)
{
	Widget* widget=findWidgetUnderMouse(event);
	
	if(widget != focusedChild)
	{
		if(focusedChild)
		{
			BlurEvent blurEvent;
			focusedChild->handleEvent(&blurEvent);
		}
	
		focusedChild=widget;
		
		if(focusedChild)
		{
			FocusEvent focusEvent;
			focusedChild->handleEvent(&focusEvent);
		}
	}
	
	if(widget)
	{
		convertAreaEventForChild(event,widget);
		widget->handleEvent(event);
	}
}

void Container::handleMouseUpEvent(MouseUpEvent* event)
{
	Widget* widget=findWidgetUnderMouse(event);

	if(widget)
	{
		convertAreaEventForChild(event,widget);
		widget->handleEvent(event);
	}
}

void Container::handleMouseOutEvent(MouseOutEvent* event)
{
	if(mouseOverChild)
	{
		MouseOutEvent mouseOutEvent;
		mouseOverChild->handleEvent(&mouseOutEvent);
		
		mouseOverChild = 0;
	}
}

void Container::handleBlurEvent(BlurEvent* event)
{
	if(focusedChild)
	{
		BlurEvent blurEvent;
		focusedChild->handleEvent(&blurEvent);
		
		focusedChild = 0;
	}
}

void Container::handleMouseMoveEvent(MouseMoveEvent* event)
{
	Widget* widget=findWidgetUnderMouse(event);
	
	if(widget != mouseOverChild)
	{
		if(mouseOverChild)
		{
			MouseOutEvent mouseOutEvent;
			mouseOverChild->handleEvent(&mouseOutEvent);
		}
	
		mouseOverChild=widget;
		
		if(mouseOverChild)
		{
			MouseOverEvent mouseOverEvent;
			mouseOverChild->handleEvent(&mouseOverEvent);
		}
	}
		
	if(mouseOverChild)
	{
		convertAreaEventForChild(event,mouseOverChild);	
		mouseOverChild->handleEvent(event);
	}
}

void Container::handleDrawEvent(DrawEvent* event)
{
	std::vector<Widget*>::iterator i;
	
	for(i=children.begin();i!=children.end();++i)
	{
		Widget* widget=(*i);
	
		if(!widget->getVisible())
			continue;
		
		DrawEvent drawEvent=*event;
		
		convertAreaEventForChild(&drawEvent,widget);
		
		{
			Scissor scissor(event->getWindow(), drawEvent.getAreaPosition(), drawEvent.getAreaSize());
			widget->handleEvent(&drawEvent);
		}
		
		if(showBounds)
		{
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
		}	
	}
}

void Container::showOnlyWidget(const std::string& name)
{
	std::vector<Widget*>::iterator i;
	
	for(i=children.begin(); i!=children.end(); ++i)
	{
		Widget* widget = *i;
	
		if(widget->getName() == name)
			widget->setVisible(true);
		else
			widget->setVisible(false);
	}
}

void Container::addWidget(Widget* child)
{
	children.push_back(child);
}

Widget& Container::getChildByName(const std::string& name)
{
	for(int i = 0; i != getChildCount(); ++i)
	{
		Widget* child = getChild(i);
		
		if(child->getName() == name)
			return *child;
	}
	
	for(int i = 0; i != getChildCount(); ++i)
	{
		Widget* child = getChild(i);
		
		Container* container = dynamic_cast<Container*>(child);
		
		if(container)
		{			
			try
			{		
				Widget& widget = container->getChildByName(name);
			
				return widget;
			}
			catch(...)
			{
			
			}
		}
	}
	
	std::stringstream ss;

	ss << "No child of name '" << name << "'";

	throw std::runtime_error(ss.str());
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
	mouseOverChild(0),
	showBounds(0)
{

}

Widget* Container::findWidgetUnderMouse(MouseEvent* event)
{
	std::vector<Widget*>::reverse_iterator i;
	
	for(i = children.rbegin(); i != children.rend(); ++i)
	{
		Widget* widget = (*i);

		if(!widget->getVisible())
			continue;
	
		MouseEvent newEvent=*event;
		
		convertAreaEventForChild(&newEvent,widget);
		
		Vector2D size = newEvent.getAreaSize();
		
		Vector2D point = newEvent.getMousePosition();
		
		bool y = point.getY() >= 0 && point.getY() <= size.getY();
		bool x = point.getX() >= 0 && point.getX() <= size.getX();
		
		if(x && y)
			return widget;
	}
	
	return 0;
}

void Container::convertAreaEventForChild(AreaEvent* event,Widget* widget)
{
	event->moveOrigin(getWidgetPosition(widget,event->getAreaSize()));
	event->setAreaSize(getWidgetSize(widget,event->getAreaSize()));
}
