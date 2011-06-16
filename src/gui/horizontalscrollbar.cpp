#include "horizontalscrollbar.hpp"

int HorizontalScrollBar::getShortAxis(Vector2D value)
{
	return value.getY();
}

int HorizontalScrollBar::getLongAxis(Vector2D value)
{
	return value.getX();
}

Vector2D HorizontalScrollBar::convertToReal(int shortAxis, int longAxis)
{
	return Vector2D(longAxis, shortAxis);
}
