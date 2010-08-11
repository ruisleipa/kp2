#ifndef MOUSEEVENT_HPP
#define MOUSEEVENT_HPP

#include <stdint.h>
#include "graphics/vector2d.hpp"

class MouseEvent
{
	public:
		Vector2D getPosition();
		
		enum MouseButton
		{
			LEFT=0,
			MIDDLE=1,
			RIGHT=2,
			WHEELUP=3,
			WHEELDOWN=4
		};
		
		bool isButtonDown(MouseButton button_index);
		
		MouseEvent(Vector2D position,int state);
		
	private:
		Vector2D m_position;
		int m_state;		
		
};

#endif // MOUSEEVENT_HPP
