#ifndef GUI_FREECONTAINER_HPP
#define GUI_FREECONTAINER_HPP

#include <map>
#include "container.hpp"

class FreeContainer : public Container
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
					AUTO
				};
				
				Type type;
		};
		
		void addWidget(Widget& widget, const std::string& left,
		const std::string top, const std::string width,
		const std::string height);
		
		void setWidgetPosition(Widget& widget, const std::string& left,
		const std::string top);
		
		virtual Vector2D getAutoSize();

	protected:
		virtual Vector2D getWidgetPosition(Widget* widget,Vector2D ourSize);
		virtual Vector2D getWidgetSize(Widget* widget,Vector2D ourSize);
	
	private:
		class Dimensions
		{
			public:
				DimensionValue left;
				DimensionValue top;
				DimensionValue width;
				DimensionValue height;
		};
		
		std::map<Widget*, Dimensions> dimensions;
};

#endif

