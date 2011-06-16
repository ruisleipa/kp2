#ifndef GUI_LAYOUTCONTAINER_HPP
#define GUI_LAYOUTCONTAINER_HPP

#include "container.hpp"

struct Layout
{
	Vector2D position;
	Vector2D size;
};

class LayoutContainer : public Container
{
	public:
		class DimensionValue
		{
			public:
				DimensionValue(const std::string& value);
				DimensionValue();
				
				float value;
				
				enum Type
				{
					PIXEL,
					RELATIVE,
					FLUID,
					AUTO
				};
				
				Type type;
		};
		
		void addWidget(Widget& widget, const std::string& width,
		const std::string& height);
		
		virtual void handleEvent(Event* event);
		
		void showOuterPadding(bool padding);
		void showInnerPadding(bool padding);
		
		Vector2D getAutoSize();
		
		LayoutContainer();
	
	protected:
		void handleDrawEvent(DrawEvent* event);
		
		virtual Vector2D getWidgetPosition(Widget* widget,Vector2D ourSize);
		virtual Vector2D getWidgetSize(Widget* widget,Vector2D ourSize);
		
		class Dimensions
		{
			public:
				DimensionValue width;
				DimensionValue height;
		};
		
		virtual float getStackedAxis(Vector2D ourSize) = 0;
		virtual float getNonStackedAxis(Vector2D ourSize) = 0;
		virtual DimensionValue getStackedDimension(const Dimensions& dimensions) = 0;
		virtual DimensionValue getNonStackedDimension(const Dimensions& dimensions) = 0;
		virtual Vector2D convertDimensionsToVector(float stacked, float nonStacked) = 0;
		
	private:
		bool applyOuterPadding;
		bool applyInnerPadding;
		
		std::map<Widget*, Dimensions> dimensions;
		
		std::map<Widget*, Vector2D> sizes;
		std::map<Widget*, Vector2D> positions;
};

#endif

