#ifndef GUI_SCROLLBOX_HPP
#define GUI_SCROLLBOX_HPP

#include "widget.hpp"
#include "widgetloader.hpp"

class ScrollBox : public Widget
{
	public:
		void addWidget(Widget& widget, const std::string width,
		const std::string height);
		
		virtual void handleEvent(Event* event);
		
		ScrollBox();
		
	private:
		void updateViewPosition();
	
		WidgetLoader loader;
		
		Widget* currentWidget;
		
};

#endif
