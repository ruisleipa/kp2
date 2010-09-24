#include "eventarea.hpp"

const Vector2D& EventArea::getPosition() const
{
	return position;	
}

const Vector2D& EventArea::getSize() const
{
	return size;
}

Window& EventArea::getWindow() const
{
	return *window;
}

EventArea::EventArea(Window& window,Vector2D position,Vector2D size):
	window(&window),
	position(position),
	size(size)	
{

}
