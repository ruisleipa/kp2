#ifndef GUI_WIDGETFACTORY_HPP
#define GUI_WIDGETFACTORY_HPP

#include <string>

#include "widgetloader.hpp"

#include "layoutcontainer.hpp"
#include "button.hpp"
#include "widget.hpp"

class WidgetFactory
{
	public:		
		Widget* build(WidgetNode& widgetNode);
				
	private:
		Widget* createWidget(const std::string& name);
		
		void applyLayoutContainerAttributes(LayoutContainer* layoutContainer, const IniFile& attributes);
		void applyTextWidgetAttributes(TextWidget* textWidget, const IniFile& attributes);
		void applyWidgetAttributes(Widget* widget, const IniFile& attributes);

};

#endif

