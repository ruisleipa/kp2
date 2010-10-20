#ifndef LAYOUTCONTAINER_HPP
#define LAYOUTCONTAINER_HPP

#include "container.hpp"

class LayoutContainer : public Container
{
	public:
		virtual void onDraw(DrawEvent event);
		
		bool showOuterPadding(bool padding);
		
		LayoutContainer();
	
	protected:
		virtual int getDividedSide(Vector2D size) = 0;
		virtual int getNonDividedSide(Vector2D size) = 0;
		virtual Vector2D convertDimensionsToVector(int dividedSide,int nonDividedSide) = 0;
	
	private:
		int getVisibleWidgetCount();
		
		bool applyOuterPadding;

};

#endif // LAYOUTCONTAINER_HPP

