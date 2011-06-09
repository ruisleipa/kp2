#include "columnlayoutcontainer.hpp"

float ColumnLayoutContainer::getStackedAxis(Vector2D ourSize)
{
	return ourSize.getX();
}

float ColumnLayoutContainer::getNonStackedAxis(Vector2D ourSize)
{
	return ourSize.getY();
}

ColumnLayoutContainer::DimensionValue ColumnLayoutContainer::getStackedDimension(const Dimensions& dimensions)
{
	return dimensions.width;
}

ColumnLayoutContainer::DimensionValue ColumnLayoutContainer::getNonStackedDimension(const Dimensions& dimensions)
{
	return dimensions.height;
}

Vector2D ColumnLayoutContainer::convertDimensionsToVector(float stacked, float nonStacked)
{
	return Vector2D(stacked, nonStacked);
}

