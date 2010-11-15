#ifndef LAYOUTCONTAINER_HPP
#define LAYOUTCONTAINER_HPP

#include "container.hpp"

struct Layout
{
	Vector2D position;
	Vector2D size;
};

class LayoutContainer : public Container
{
	public:
		virtual void handleEvent(Event* event);
		
		bool showOuterPadding(bool padding);
		
		LayoutContainer();
	
	protected:
		void handleDrawEvent(DrawEvent* event);
	
		virtual int getDividedAxis(Vector2D size) = 0;
		virtual int getNonDividedAxis(Vector2D size) = 0;
		virtual Vector2D convertDimensionsToVector(int dividedSide,int nonDividedSide) = 0;
		
		virtual Vector2D getWidgetPosition(Widget* widget,Vector2D ourSize);
		virtual Vector2D getWidgetSize(Widget* widget,Vector2D ourSize);
	
	private:
		int getVisibleWidgetCount();
		int calculateTotalSizeOfFluidWidgets(Vector2D ourSize);
		int calculateTotalSizeOfNonFluidWidgets(Vector2D ourSize);
		
		bool applyOuterPadding;		
		
		std::map<Widget*,Layout> layouts;
};

#endif // LAYOUTCONTAINER_HPP

