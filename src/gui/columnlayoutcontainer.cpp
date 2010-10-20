#include "columnlayoutcontainer.hpp"

int ColumnLayoutContainer::getDividedSide(Vector2D size)
{
	return size.getX();
}

int ColumnLayoutContainer::getNonDividedSide(Vector2D size)
{
	return size.getY();
}

Vector2D ColumnLayoutContainer::convertDimensionsToVector(int dividedSide,int nonDividedSide)
{
	return Vector2D(dividedSide,nonDividedSide);
}
