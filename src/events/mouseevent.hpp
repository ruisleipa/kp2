#ifndef MOUSEEVENT_HPP
#define MOUSEEVENT_HPP

#include "event.hpp"

#include "graphics/vector2d.hpp"

class MouseEvent: public Event
{
	public:
		Vector2D getMousePosition();
		
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

#endif // MOUSEEVENT_HPP
