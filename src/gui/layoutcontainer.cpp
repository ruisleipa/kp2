#include "LayoutContainer.hpp"

const float PADDING=10;

void LayoutContainer::handleEvent(Event* event)
{
	if(dynamic_cast<DrawEvent*>(event))
		handleDrawEvent(dynamic_cast<DrawEvent*>(event));
	
	Container::handleEvent(event);
}

void LayoutContainer::handleDrawEvent(DrawEvent* event)
{
	int dividedAxis = getDividedAxis(event->getAreaSize());
	int sizeAvailableForWidgets = dividedAxis - (getVisibleWidgetCount() - 1) * PADDING;
	int nonDividedAxis = getNonDividedAxis(event->getAreaSize());
	int outerPadding=0;
	int position=0;
	
	if(applyOuterPadding)
	{
		sizeAvailableForWidgets -= PADDING * 2;
		nonDividedAxis -= PADDING * 2;
		outerPadding = PADDING;
		position = PADDING;
	}
	
	int sizeAvailableForFluidWidgets = sizeAvailableForWidgets - calculateTotalSizeOfNonFluidWidgets(event->getAreaSize());
	int totalSizeOfFluidWidgets = calculateTotalSizeOfFluidWidgets(event->getAreaSize());
	
	layouts.clear();
	
	for(int i=0;i<getChildCount();i++)
	{
		Widget* child = getChild(i);
		
		if(!child)
			continue;
			
		if(child->getVisible())
		{
			int widgetSize = getDividedAxis(calculateWidgetSize(child,event->getAreaSize()));
		
			if(child->getFluid())
			{
				if(widgetSize == 0)
					widgetSize = 1;
				
				float ratio = float(widgetSize) / float(totalSizeOfFluidWidgets);
				
				widgetSize = sizeAvailableForFluidWidgets * ratio;
			}
		
			Layout layout;
			
			layout.position = convertDimensionsToVector(position,outerPadding);
			layout.size = convertDimensionsToVector(widgetSize,nonDividedAxis);
			
			layouts[child] = layout;
			
			position += widgetSize;
			position += PADDING;		
		}
	}	
}

void LayoutContainer::showOuterPadding(bool padding)
{
	applyOuterPadding = padding;
}

LayoutContainer::LayoutContainer():
	applyOuterPadding(true)
{

}

int LayoutContainer::getVisibleWidgetCount()
{
	int count=0;

	for(int i=0;i<getChildCount();i++)
	{
		Widget* child=getChild(i);
		
		if(!child)
			continue;
			
		if(child->getVisible())
			count++;
	}
	
	return count;
}

int LayoutContainer::calculateTotalSizeOfFluidWidgets(Vector2D ourSize)
{
	int totalsize=0;

	for(int i=0;i<getChildCount();i++)
	{
		Widget* child=getChild(i);
		
		if(!child)
			continue;
			
		if(!child->getVisible())
			continue;
			
		if(child->getFluid())
		{
			int size = getDividedAxis(calculateWidgetSize(child,ourSize));
		
			if(size == 0)
				size = 1;
		
			totalsize += size;
		}
	}
	
	return totalsize;
}

int LayoutContainer::calculateTotalSizeOfNonFluidWidgets(Vector2D ourSize)
{
	int totalsize=0;

	for(int i=0;i<getChildCount();i++)
	{
		Widget* child=getChild(i);
		
		if(!child)
			continue;
			
		if(!child->getVisible())
			continue;
			
		if(!child->getFluid())
			totalsize += getDividedAxis(calculateWidgetSize(child,ourSize));
	}
	
	return totalsize;
}

Vector2D LayoutContainer::getWidgetPosition(Widget* widget,Vector2D ourSize)
{
	return layouts[widget].position;
}

Vector2D LayoutContainer::getWidgetSize(Widget* widget,Vector2D ourSize)
{
	return layouts[widget].size;
}
