#include "widgetfactory.hpp"

#include "button.hpp"
#include "label.hpp"
#include "graph.hpp"
#include "columnlayoutcontainer.hpp"
#include "rowlayoutcontainer.hpp"

Widget* WidgetFactory::build(WidgetNode& node)
{
	Widget* widget;
	
	if(node.type == "RowLayout")
		widget = new RowLayoutContainer();
	else if(node.type == "ColumnLayout")
		widget = new ColumnLayoutContainer();
	else if(node.type == "Button")
		widget = new Button();
	else if(node.type == "Label")
		widget = new Label();
	else if(node.type == "Graph")
		widget = new Graph();	
	
	if(dynamic_cast<LayoutContainer*>(widget))
		applyLayoutContainerAttributes(dynamic_cast<LayoutContainer*>(widget), node.attributes);
	if(dynamic_cast<TextWidget*>(widget))
		applyTextWidgetAttributes(dynamic_cast<TextWidget*>(widget), node.attributes);
	
	applyWidgetAttributes(widget, node.attributes);
	
	return widget;
}

void WidgetFactory::applyLayoutContainerAttributes(LayoutContainer* layoutContainer, const IniFile& attributes)
{
	layoutContainer->showOuterPadding(attributes.getValueWithDefault("showOuterPadding", 1));
}

void WidgetFactory::applyTextWidgetAttributes(TextWidget* textWidget, const IniFile& attributes)
{
	textWidget->setText(attributes.getValueWithDefault("text", ""));
}

void WidgetFactory::applyWidgetAttributes(Widget* widget, const IniFile& attributes)
{
	widget->setName(attributes.getValueWithDefault("name", ""));
	widget->setFluid(attributes.getValueWithDefault("fluid", 0));
	widget->setVisible(attributes.getValueWithDefault("visible", 1));
	
	float width = attributes.getValueWithDefault("width", 0.0);
	float height = attributes.getValueWithDefault("height", 0.0);
	
	std::string size = attributes.getValueWithDefault("size", "");
	
	if(size == "pixel")
		widget->setPixelSize(Vector2D(width, height));
	else if(size == "factor")
		widget->setFactorSize(Vector2D(width, height));
}

