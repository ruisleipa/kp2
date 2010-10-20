#include "mouseevent.hpp"

#include "debug/assert.hpp"

Vector2D MouseEvent::getMousePosition()
{
	return mousePosition;
}

void MouseEvent::moveOrigin(const Vector2D& offset)
{
	mousePosition -= offset;
	
	Event::moveOrigin(offset);
}

bool MouseEvent::isButtonDown(MouseButton button)
{
	assert(button < 5);
	
	return state & (1 << button);
}

MouseEvent::MouseEvent(const EventArea& area,const Vector2D& mousePosition,int state):
	Event(area),
	mousePosition(mousePosition),
	state(state)	
{

}
