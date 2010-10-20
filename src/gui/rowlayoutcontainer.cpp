#include "rowlayoutcontainer.hpp"

int RowLayoutContainer::getDividedSide(Vector2D size)
{
	return size.getY();
}

int RowLayoutContainer::getNonDividedSide(Vector2D size)
{
	return size.getX();
}

Vector2D RowLayoutContainer::convertDimensionsToVector(int dividedSide,int nonDividedSide)
{
	return Vector2D(nonDividedSide,dividedSide);
}
