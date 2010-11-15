#ifndef ROWLAYOUTCONTAINER_HPP
#define ROWLAYOUTCONTAINER_HPP

#include "layoutcontainer.hpp"

class RowLayoutContainer : public LayoutContainer
{
	protected:
		virtual int getDividedAxis(Vector2D size);
		virtual int getNonDividedAxis(Vector2D size);
		virtual Vector2D convertDimensionsToVector(int dividedAxis,int nonDividedAxis);

};

#endif // ROWLAYOUTCONTAINER_HPP

