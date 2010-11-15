#include "rowlayoutcontainer.hpp"

int RowLayoutContainer::getDividedAxis(Vector2D size)
{
	return size.getY();
}

int RowLayoutContainer::getNonDividedAxis(Vector2D size)
{
	return size.getX();
}

Vector2D RowLayoutContainer::convertDimensionsToVector(int dividedAxis,int nonDividedAxis)
{
	return Vector2D(nonDividedAxis,dividedAxis);
}
