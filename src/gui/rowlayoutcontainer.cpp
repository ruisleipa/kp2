#include "rowlayoutcontainer.hpp"

float RowLayoutContainer::getStackedAxis(Vector2D ourSize)
{
	return ourSize.getY();
}

float RowLayoutContainer::getNonStackedAxis(Vector2D ourSize)
{
	return ourSize.getX();
}

RowLayoutContainer::DimensionValue RowLayoutContainer::getStackedDimension(const Dimensions& dimensions)
{
	return dimensions.height;
}

RowLayoutContainer::DimensionValue RowLayoutContainer::getNonStackedDimension(const Dimensions& dimensions)
{
	return dimensions.width;
}

Vector2D RowLayoutContainer::convertDimensionsToVector(float stacked, float nonStacked)
{
	return Vector2D(nonStacked, stacked);
}

