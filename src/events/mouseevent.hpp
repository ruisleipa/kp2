#ifndef MOUSEEVENT_HPP
#define MOUSEEVENT_HPP

#include "areaevent.hpp"

#include "graphics/vector2d.hpp"

class MouseEvent: public AreaEvent
{
	public:
		Vector2D getMousePosition();
		
		virtual void moveOrigin(const Vector2D& offset);
		
		enum MouseButton
		{
			LEFT=0,
			MIDDLE=1,
			RIGHT=2,
			WHEELUP=3,
			WHEELDOWN=4
		};
		
		bool isButtonDown(MouseButton button);
		
		MouseEvent(const EventArea& area,const Vector2D& mousePosition,int state);
		
	private:
		Vector2D mousePosition;
		int state;
		
};

class MouseUpEvent: public MouseEvent
{
	public:
		MouseUpEvent(const EventArea& area,const Vector2D& mousePosition,int state):
			MouseEvent(area,mousePosition,state)
		{
		
		}
};

class MouseDownEvent: public MouseEvent
{
	public:
		MouseDownEvent(const EventArea& area,const Vector2D& mousePosition,int state):
			MouseEvent(area,mousePosition,state)
		{
		
		}
};

class MouseMoveEvent: public MouseEvent
{
	public:
		MouseMoveEvent(const EventArea& area,const Vector2D& mousePosition,int state):
			MouseEvent(area,mousePosition,state)
		{
		
		}
};

class MouseOverEvent: public Event
{

};

class MouseOutEvent: public Event
{

};

#endif // MOUSEEVENT_HPP
