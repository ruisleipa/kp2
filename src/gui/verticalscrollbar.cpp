#include "verticalscrollbar.hpp"

int VerticalScrollBar::getShortAxis(Vector2D value)
{
	return value.getX();
}

int VerticalScrollBar::getLongAxis(Vector2D value)
{
	return value.getY();
}

Vector2D VerticalScrollBar::convertToReal(int shortAxis, int longAxis)
{
	return Vector2D(shortAxis, longAxis);
}
