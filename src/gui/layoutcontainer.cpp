#include "layoutcontainer.hpp"

#include "utils/string.hpp"

const float PADDING=10;

LayoutContainer::DimensionValue::DimensionValue(const std::string& value)
{
	const std::string pixelSuffix = "px";
	const std::string relativeSuffix = "%";
	const std::string fluidSuffix = "~";
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
	else if(value.substr(value.size() - fluidSuffix.size()) == fluidSuffix)
	{
		this->value = convertTo<float>(value.substr(0, value.size() - fluidSuffix.size()));
		this->type = FLUID;
	}
}

LayoutContainer::DimensionValue::DimensionValue()
{
	this->value = 0.0;
	this->type = AUTO;
}

void LayoutContainer::addWidget(Widget& widget, const std::string& w, const std::string& h)
{
	DimensionValue width(w);
	DimensionValue height(h);
	
	Container::addWidget(&widget);
	
	Dimensions widgetDimensions;
	
	widgetDimensions.width = width;
	widgetDimensions.height = height;
	
	dimensions[&widget] = widgetDimensions;
}

void LayoutContainer::handleEvent(Event* event)
{
	if(dynamic_cast<DrawEvent*>(event))
		handleDrawEvent(dynamic_cast<DrawEvent*>(event));
	
	Container::handleEvent(event);
}

void LayoutContainer::handleDrawEvent(DrawEvent* event)
{
	int spaceAvailable = getStackedAxis(event->getAreaSize());
	int nonStackedSpaceAvailable = getNonStackedAxis(event->getAreaSize());
	
	if(applyOuterPadding)
	{
		spaceAvailable -= PADDING * 2;
		nonStackedSpaceAvailable -= PADDING * 2;
	}
	
	//remove padding from available spacing
	int visibleWidgetCount = 0;
	
	for(int i=0; i < getChildCount(); i++)
	{
		if(getChild(i)->getVisible())
			visibleWidgetCount++;
	}
	
	if(applyInnerPadding)
		spaceAvailable -= PADDING * (visibleWidgetCount - 1);
	
	//calculate size occupied by widgets with non fluid dimensions	
	float totalSizeOfNonFluidWidgets = 0;
	
	for(int i=0; i < getChildCount(); i++)
	{
		Widget* child = getChild(i);
		
		if(!child->getVisible())
			continue;
			
		Dimensions childDimensions = dimensions[child];
		
		DimensionValue dimension = getStackedDimension(childDimensions);
		
		if(dimension.type == DimensionValue::FLUID)
			continue;
		if(dimension.type == DimensionValue::AUTO)
			totalSizeOfNonFluidWidgets += getStackedAxis(child->getAutoSize());
		if(dimension.type == DimensionValue::PIXEL)
			totalSizeOfNonFluidWidgets += dimension.value;
		if(dimension.type == DimensionValue::RELATIVE)
			totalSizeOfNonFluidWidgets += dimension.value * spaceAvailable;
	}
	
	//calculate total fluid proportion value
	float totalFluidProportionValue = 0;
	
	for(int i=0; i < getChildCount(); i++)
	{
		Widget* child = getChild(i);
		
		if(!child->getVisible())
			continue;
			
		Dimensions childDimensions = dimensions[child];
		
		DimensionValue dimension = getStackedDimension(childDimensions);
		
		if(dimension.type == DimensionValue::FLUID)
			totalFluidProportionValue += dimension.value;
	}
	
	float totalSpaceForFluidWidgets = spaceAvailable - totalSizeOfNonFluidWidgets;
	
	sizes.clear();
	positions.clear();
	
	float position = 0;
	float nonStackedPosition = 0;
	
	if(applyOuterPadding)
	{
		position = PADDING;
		nonStackedPosition = PADDING;
	}
	
	for(int i=0; i < getChildCount(); i++)
	{
		Widget* child = getChild(i);
		
		if(!child->getVisible())
			continue;
			
		Dimensions childDimensions = dimensions[child];
		
		DimensionValue stackedDimension = getStackedDimension(childDimensions);
		DimensionValue nonStackedDimension = getNonStackedDimension(childDimensions);
		
		float stackedSize = 0;
		float nonStackedSize = 0;
		
		if(stackedDimension.type == DimensionValue::FLUID)
			stackedSize = stackedDimension.value / totalFluidProportionValue * totalSpaceForFluidWidgets;
		else if(stackedDimension.type == DimensionValue::PIXEL)
			stackedSize = stackedDimension.value;
		else if(stackedDimension.type == DimensionValue::AUTO)
			stackedSize = getStackedAxis(child->getAutoSize());
		else if(stackedDimension.type == DimensionValue::RELATIVE)
			stackedSize = stackedDimension.value * spaceAvailable;
			
		if(nonStackedDimension.type == DimensionValue::FLUID)
			nonStackedSize = 0;
		else if(nonStackedDimension.type == DimensionValue::PIXEL)
			nonStackedSize = nonStackedDimension.value;
		else if(nonStackedDimension.type == DimensionValue::AUTO)
			nonStackedSize = getNonStackedAxis(child->getAutoSize());
		else if(nonStackedDimension.type == DimensionValue::RELATIVE)
			nonStackedSize = nonStackedDimension.value * nonStackedSpaceAvailable;
			
		sizes[child] = convertDimensionsToVector(stackedSize, nonStackedSize);
		positions[child] = convertDimensionsToVector(position, nonStackedPosition);
		
		position += stackedSize;
		
		if(applyInnerPadding)
			position += PADDING;
	}
}

Vector2D LayoutContainer::getAutoSize()
{
	float totalStackedSize = 0;
	float totalNonStackedSize = 0;
	int visibleWidgetCount = 0;
	
	for(int i=0; i < getChildCount(); i++)
	{
		Widget* child = getChild(i);
		
		if(!child->getVisible())
			continue;
		
		visibleWidgetCount++;
		
		Dimensions childDimensions = dimensions[child];
		
		DimensionValue stackedDimension = getStackedDimension(childDimensions);
		DimensionValue nonStackedDimension = getNonStackedDimension(childDimensions);
		
		float stackedSize = 0;
		float nonStackedSize = 0;
		
		if(stackedDimension.type == DimensionValue::PIXEL)
			stackedSize = stackedDimension.value;
		else if(stackedDimension.type == DimensionValue::AUTO)
			stackedSize = getStackedAxis(child->getAutoSize());

		if(nonStackedDimension.type == DimensionValue::PIXEL)
			nonStackedSize = nonStackedDimension.value;
		else if(nonStackedDimension.type == DimensionValue::AUTO)
			nonStackedSize = getNonStackedAxis(child->getAutoSize());
		
		totalStackedSize += stackedSize;
		
		
		
		totalNonStackedSize = std::max(totalNonStackedSize, nonStackedSize);
	}
	
	if(applyOuterPadding)
	{
		totalStackedSize += PADDING * 2;
		totalNonStackedSize += PADDING * 2;
	}
	
	if(applyInnerPadding && visibleWidgetCount > 1)
		totalStackedSize += PADDING * (visibleWidgetCount - 1);
	
	return convertDimensionsToVector(totalStackedSize, totalNonStackedSize);
}

LayoutContainer::LayoutContainer():
	applyOuterPadding(true),
	applyInnerPadding(true)
{

}

Vector2D LayoutContainer::getWidgetPosition(Widget* widget,Vector2D ourSize)
{
	return positions[widget];
}

Vector2D LayoutContainer::getWidgetSize(Widget* widget,Vector2D ourSize)
{
	return sizes[widget];
}

void LayoutContainer::showOuterPadding(bool padding)
{
	applyOuterPadding = padding;
}

void LayoutContainer::showInnerPadding(bool padding)
{
	applyInnerPadding = padding;
}
