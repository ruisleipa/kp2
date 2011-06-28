#ifndef GUI_SCROLLBOX_HPP
#define GUI_SCROLLBOX_HPP

#include "widget.hpp"
#include "widgetloader.hpp"

#include "container.hpp"

class ScrollBox : public Container
{
	public:
		void addWidget(Widget& widget, const std::string width,
		const std::string height);
		
		virtual void handleEvent(Event* event);
		
		ScrollBox();

	protected:
		virtual Vector2D getWidgetPosition(Widget* widget,Vector2D ourSize);
		virtual Vector2D getWidgetSize(Widget* widget,Vector2D ourSize);
		
	private:
		void updateViewPosition();
	
		WidgetLoader loader;
		
		Widget* currentWidget;
		
};

#endif
