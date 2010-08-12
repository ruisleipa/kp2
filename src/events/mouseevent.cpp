#include "mouseevent.hpp"

#include "debug/assert.hpp"

#include <iostream>

Vector2D MouseEvent::getPosition()
{
	return position;
}

bool MouseEvent::isButtonDown(MouseButton button_index)
{
	assert(button_index < 5);
	
	return state & (1 << button_index);
}

Window& MouseEvent::getWindow()
{
	return window;
}

MouseEvent::MouseEvent(Window& window,Vector2D position,int state):
	window(window),
	position(position),
	state(state)	
{

}
