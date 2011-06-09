#ifndef GUI_WIDGETFACTORY_HPP
#define GUI_WIDGETFACTORY_HPP

#include <string>

#include "widgetloader.hpp"

class Widget;
class LayoutContainer;
class TextWidget;
class Image;
class Gauge;

class WidgetFactory
{
	public:		
		Widget* build(WidgetNode& widgetNode);
				
	private:
		Widget* createWidget(const std::string& name);
		
		void applyAttributes(LayoutContainer* layoutContainer, const IniFile& attributes);
		void applyAttributes(TextWidget* textWidget, const IniFile& attributes);
		void applyAttributes(Image* image, const IniFile& attributes);
		void applyAttributes(Widget* widget, const IniFile& attributes);

};

#endif

