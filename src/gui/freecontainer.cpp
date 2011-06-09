#include "freecontainer.hpp"

#include "utils/string.hpp"

FreeContainer::DimensionValue::DimensionValue(const std::string& value)
{
	const std::string pixelSuffix = "px";
	const std::string relativeSuffix = "%";
	const std::string autoValue = "auto";
	
	if(value == autoValue)
	{
		this->value = 0.0;
		this->type = AUTO;
	}
	else if(value.substr(value.size() - pixelSuffix.size()) == pixelSuffix)
	{
		this->value = convertTo<float>(value.substr(0, value.size() - pixelSuffix.size()));
		this->type = PIXEL;
	}
	else if(value.substr(value.size() - relativeSuffix.size()) == relativeSuffix)
	{
		this->value = convertTo<float>(value.substr(0, value.size() - relativeSuffix.size()));
		this->value /= 100.0;
		this->type = RELATIVE;
	}
}

FreeContainer::DimensionValue::DimensionValue()
{
	this->value = 0.0;
	this->type = AUTO;
}

void FreeContainer::addWidget(Widget& widget,const std::string& l,
const std::string t, const std::string w,const std::string h)
{
	Container::addWidget(&widget);
	
	DimensionValue left(l);
	DimensionValue top(t);
	DimensionValue width(w);
	DimensionValue height(h);
	
	Dimensions widgetDimensions;
	
	widgetDimensions.left = left;
	widgetDimensions.top = top;
	widgetDimensions.width = width;
	widgetDimensions.height = height;
	
	dimensions[&widget] = widgetDimensions;
}

Vector2D FreeContainer::getAutoSize()
{
	float width = 0;
	float height = 0;
	
	for(int i = 0; i < getChildCount(); ++i)
	{
		Widget* widget = getChild(i);
		
		Dimensions widgetDimensions = dimensions[widget];
		
		if(widgetDimensions.left.type == DimensionValue::PIXEL)
		{
			if(widgetDimensions.width.type == DimensionValue::PIXEL)
				width = std::max(width, widgetDimensions.left.value + widgetDimensions.width.value);
			else if(widgetDimensions.width.type == DimensionValue::AUTO)
				width = std::max(width, widgetDimensions.left.value + widget->getAutoSize().getX());
		}
		
		if(widgetDimensions.top.type == DimensionValue::PIXEL)
		{
			if(widgetDimensions.height.type == DimensionValue::PIXEL)
				height = std::max(height, widgetDimensions.top.value + widgetDimensions.height.value);
			else if(widgetDimensions.height.type == DimensionValue::AUTO)
				height = std::max(height, widgetDimensions.top.value + widget->getAutoSize().getY());
		}
	}
	
	return Vector2D(width, height);
}

Vector2D FreeContainer::getWidgetPosition(Widget* widget, Vector2D ourSize)
{
	Dimensions widgetDimensions = dimensions[widget];

	float left = widgetDimensions.left.value;
	float top = widgetDimensions.top.value;
	
	if(widgetDimensions.left.type == DimensionValue::RELATIVE)
		left *= ourSize.getX();
		
	if(widgetDimensions.top.type == DimensionValue::RELATIVE)
		top *= ourSize.getY();
	
	Vector2D position(left, top);
	
	return position;
}

Vector2D FreeContainer::getWidgetSize(Widget* widget, Vector2D ourSize)
{
	Dimensions widgetDimensions = dimensions[widget];

	float width = widgetDimensions.width.value;
	float height = widgetDimensions.height.value;
	
	if(widgetDimensions.width.type == DimensionValue::AUTO)
		width = widget->getAutoSize().getX();
		
	if(widgetDimensions.height.type == DimensionValue::AUTO)
		height = widget->getAutoSize().getY();
	
	if(widgetDimensions.width.type == DimensionValue::RELATIVE)
		width *= ourSize.getX();
		
	if(widgetDimensions.height.type == DimensionValue::RELATIVE)
		height *= ourSize.getY();
	
	Vector2D size(width, height);
	
	return size;
}

