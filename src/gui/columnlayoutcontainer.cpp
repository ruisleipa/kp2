#include "columnlayoutcontainer.hpp"

int ColumnLayoutContainer::getDividedAxis(Vector2D size)
{
	return size.getX();
}

int ColumnLayoutContainer::getNonDividedAxis(Vector2D size)
{
	return size.getY();
}

Vector2D ColumnLayoutContainer::convertDimensionsToVector(int dividedAxis,int nonDividedAxis)
{
	return Vector2D(dividedAxis,nonDividedAxis);
}
