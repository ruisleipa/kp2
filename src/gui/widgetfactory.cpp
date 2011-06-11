#include "widgetfactory.hpp"

#include "button.hpp"
#include "label.hpp"
#include "field.hpp"
#include "graph.hpp"
#include "listbox.hpp"
#include "select.hpp"
#include "graphics/texture.hpp"
#include "columnlayoutcontainer.hpp"
#include "rowlayoutcontainer.hpp"
#include "client/playervehiclewidget.hpp"
#include "client/gauge.hpp"

Widget* WidgetFactory::build(WidgetNode& node)
{
	Widget* widget = NULL;
	
	if(node.type == "RowLayout")
		widget = new RowLayoutContainer();
	else if(node.type == "ColumnLayout")
		widget = new ColumnLayoutContainer();
	else if(node.type == "FreeLayout")
		widget = new FreeContainer();
	else if(node.type == "Button")
		widget = new Button();
	else if(node.type == "Label")
		widget = new Label();
	else if(node.type == "Field")
		widget = new Field();
	else if(node.type == "Graph")
		widget = new Graph();
	else if(node.type == "Image")
		widget = new Image();
	else if(node.type == "ListBox")
		widget = new Listbox();
	else if(node.type == "PlayerVehicleWidget")
		widget = new PlayerVehicleWidget();
	else if(node.type == "Select")
		widget = new Select();
	else if(node.type == "Gauge")
		widget = new Gauge();
	else if(node.type == "Spacer")
		widget = new Widget();
	
	if(dynamic_cast<LayoutContainer*>(widget))
		applyAttributes(dynamic_cast<LayoutContainer*>(widget), node.attributes);
	if(dynamic_cast<TextWidget*>(widget))
		applyAttributes(dynamic_cast<TextWidget*>(widget), node.attributes);
	if(dynamic_cast<Image*>(widget))
		applyAttributes(dynamic_cast<Image*>(widget), node.attributes);
	if(dynamic_cast<Gauge*>(widget))
		applyAttributes(dynamic_cast<Gauge*>(widget), node.attributes);
	if(dynamic_cast<Widget*>(widget))
		applyAttributes(widget, node.attributes);
	
	
	return widget;
}

void WidgetFactory::applyAttributes(LayoutContainer* layoutContainer, const IniFile& attributes)
{
	layoutContainer->showOuterPadding(attributes.getValueWithDefault("showOuterPadding", 0));
}

void WidgetFactory::applyAttributes(TextWidget* textWidget, const IniFile& attributes)
{
	textWidget->setText(attributes.getValueWithDefault("text", ""));
	
	std::string font = attributes.getValueWithDefault("font", "");
	
	if(font != "")
		textWidget->setFont(Font(font));
}

void WidgetFactory::applyAttributes(Image* image, const IniFile& attributes)
{
	std::string filename = attributes.getValueWithDefault("file", "");
	
	if(filename != "")
		image->setTexture(Texture(filename));
}

void WidgetFactory::applyAttributes(Widget* widget, const IniFile& attributes)
{
	widget->setName(attributes.getValueWithDefault("name", ""));
	widget->setVisible(attributes.getValueWithDefault("visible", 1));
}

void WidgetFactory::applyAttributes(Gauge* gauge, const IniFile& attributes)
{
	float minValue = attributes.getValueWithDefault("minValue", 0.0);
	float maxValue = attributes.getValueWithDefault("maxValue", 100.0);
	float minAngle = attributes.getValueWithDefault("minAngle", 0.0);
	float maxAngle = attributes.getValueWithDefault("maxAngle", 0.0);

	gauge->setValueRange(minValue, maxValue);
	gauge->setAngleRange(minAngle, maxAngle);

	std::string gaugeFileName = attributes.getValueWithDefault("gauge", "");

	if(gaugeFileName != "")
		gauge->setGaugeTexture(Texture(gaugeFileName));

	std::string needleFileName = attributes.getValueWithDefault("needle", "");

	if(needleFileName != "")
		gauge->setNeedleTexture(Texture(needleFileName));
}

