#ifndef ROWLAYOUTCONTAINER_HPP
#define ROWLAYOUTCONTAINER_HPP

#include "layoutcontainer.hpp"

class RowLayoutContainer : public LayoutContainer
{
	protected:
		virtual float getStackedAxis(Vector2D ourSize);
		virtual float getNonStackedAxis(Vector2D ourSize);
		virtual DimensionValue getStackedDimension(const Dimensions& dimensions);
		virtual DimensionValue getNonStackedDimension(const Dimensions& dimensions);
		virtual Vector2D convertDimensionsToVector(float stacked, float nonStacked);

};

#endif // ROWLAYOUTCONTAINER_HPP

