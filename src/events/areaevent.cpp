#include "areaevent.hpp"

const Vector2D& AreaEvent::getAreaPosition()
{
	return area.getPosition();
}

void AreaEvent::moveOrigin(const Vector2D& offset)
{
	area = EventArea(area.getWindow(), area.getPosition() + offset, area.getSize());
}

const Vector2D& AreaEvent::getAreaSize()
{
	return area.getSize();
}

void AreaEvent::setAreaSize(const Vector2D& size)
{
	area = EventArea(area.getWindow(), area.getPosition(), size);
}

Window& AreaEvent::getWindow()
{
	return area.getWindow();
}

AreaEvent::AreaEvent(const EventArea& area):
	area(area)	
{

}
