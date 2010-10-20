#ifndef ROWLAYOUTCONTAINER_HPP
#define ROWLAYOUTCONTAINER_HPP

#include "layoutcontainer.hpp"

class RowLayoutContainer : public LayoutContainer
{
	protected:
		virtual int getDividedSide(Vector2D size);
		virtual int getNonDividedSide(Vector2D size);
		virtual Vector2D convertDimensionsToVector(int dividedSide,int nonDividedSide);

};

#endif // ROWLAYOUTCONTAINER_HPP

