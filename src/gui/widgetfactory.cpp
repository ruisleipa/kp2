#include "widgetfactory.hpp"

#include "button.hpp"
#include "label.hpp"
#include "field.hpp"
#include "graph.hpp"
#include "listbox.hpp"
#include "select.hpp"
#include "verticalscrollbar.hpp"
#include "horizontalscrollbar.hpp"
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
	else if(node.type == "VerticalScrollBar")
		widget = new VerticalScrollBar();
	else if(node.type == "HorizontalScrollBar")
		widget = new HorizontalScrollBar();
	
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
	
	std::string scalingMode = attributes.getValueWithDefault("scaling", "");
	
	if(scalingMode == "none")
		image->setScalingMode(Image::NONE);
	else if(scalingMode == "proportional")
		image->setScalingMode(Image::PROPORTIONAL);
	else if(scalingMode == "proportionalfill")
		image->setScalingMode(Image::PROPORTIONAL_FILL);
	else if(scalingMode == "stretchfill")
		image->setScalingMode(Image::STRETCH_FILL);
	else if(scalingMode == "nineslice")
		image->setScalingMode(Image::NINE_SLICE);
	
	int border = attributes.getValueWithDefault("nineScaleBorder", 0);
	
	int left = border;
	int top = border;
	int right = border;
	int bottom = border;
	
	try
	{
		attributes.getValue("nineScaleLeft", left);
	}
	catch(...){}
	
	try
	{
		attributes.getValue("nineScaleTop", top);
	}
	catch(...){}
	
	try
	{
		attributes.getValue("nineScaleRight", right);
	}
	catch(...){}
	
	try
	{
		attributes.getValue("nineScaleBottom", bottom);
	}
	catch(...){}
	
	image->setNineSliceCorners(Vector2D(left, top), Vector2D(right, bottom));
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

