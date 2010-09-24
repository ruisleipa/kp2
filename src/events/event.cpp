#include "event.hpp"

const Vector2D& Event::getAreaPosition()
{
	return area.getPosition();
}

void Event::moveArea(const Vector2D& offset)
{
	area = EventArea(area.getWindow(), area.getPosition() + offset, area.getSize());
}

const Vector2D& Event::getAreaSize()
{
	return area.getSize();
}

void Event::setAreaSize(const Vector2D& size)
{
	area = EventArea(area.getWindow(), area.getPosition(), size);
}

Window& Event::getWindow()
{
	return area.getWindow();
}

Event::Event(const EventArea& area):
	area(area)	
{

}
