#ifndef COLUMNLAYOUTCONTAINER_HPP
#define COLUMNLAYOUTCONTAINER_HPP

#include "layoutcontainer.hpp"

class ColumnLayoutContainer : public LayoutContainer
{
	protected:
		virtual int getDividedAxis(Vector2D size);
		virtual int getNonDividedAxis(Vector2D size);
		virtual Vector2D convertDimensionsToVector(int dividedAxis,int nonDividedAxis);

};

#endif // COLUMNLAYOUTCONTAINER_HPP

