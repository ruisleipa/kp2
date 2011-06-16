#ifndef GUI_WIDGETLOADER_HPP
#define GUI_WIDGETLOADER_HPP

#include <stack>
#include <string>
#include <vector>
#include <tr1/memory>

#include "widget.hpp"

class ScrollBox;
class FreeContainer;
class LayoutContainer;

class WidgetLine
{
	public:
		int level;
		std::string type;		
		IniFile attributes;
		
		WidgetLine():
			level(0)
		{
			
		}
};

class WidgetNode
{
	public:
		std::string type;		
		IniFile attributes;
		
		std::vector<WidgetNode> children;
};

class WidgetLoader
{
	public:
		Widget& getRootWidget();

		WidgetLoader(const std::string& filename);
				
	private:
		void load(const std::string& filename);
		
		WidgetLine parseLine(std::string line);
		IniFile parseAttributes(std::string line);
		
		void convertWidgetLines(WidgetNode& node, std::vector<WidgetLine> lines);
		
		Widget* createWidgets(WidgetNode& rootNode);
		
		void addWidgetToContainer(LayoutContainer* container, Widget* widget, const IniFile& attributes);
		void addWidgetToContainer(FreeContainer* container, Widget* widget, const IniFile& attributes);
		void addWidgetToContainer(ScrollBox* container, Widget* widget, const IniFile& attributes);
		
		std::vector<std::tr1::shared_ptr<Widget> > widgets;	
};

#endif

