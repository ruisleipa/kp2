#include "mouseevent.hpp"

#include "debug/assert.hpp"

#include <iostream>

Vector2D MouseEvent::getPosition()
{
	return m_position;
}

bool MouseEvent::isButtonDown(MouseButton button_index)
{
	assert(button_index < 5);
	
	return m_state & (1 << button_index);
}

MouseEvent::MouseEvent(Vector2D position,int state)
{
	m_position = position;
	m_state = state;
}
