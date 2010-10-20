#include "LayoutContainer.hpp"

const float PADDING=10;

void LayoutContainer::onDraw(DrawEvent event)
{
	int visibleChildrenCount = getVisibleWidgetCount();

	if(visibleChildrenCount == 0)
		return;
	
	int dividedSize=getDividedSide(event.getAreaSize());
	int nonDividedSize=getNonDividedSide(event.getAreaSize());
	
	if(applyOuterPadding)
	{
		dividedSize -= PADDING * 2;
		nonDividedSize -= PADDING * 2;
	}		
	
	dividedSize -= PADDING * (visibleChildrenCount - 1);
	dividedSize /= visibleChildrenCount;
	
	int outerPadding=0;
	int position=0;
	
	if(applyOuterPadding)
	{
		outerPadding = PADDING;
		position = PADDING;
	}
	
	for(int i=0;i<getChildCount();i++)
	{
		Widget* child=getChild(i);
		
		if(!child)
			continue;
			
		if(child->getVisible())
		{
			child->setPixelPosition(convertDimensionsToVector(position,outerPadding));
			child->setPixelSize(convertDimensionsToVector(dividedSize,nonDividedSize));
			
			position += dividedSize;
			position += PADDING;			
		}
	}	
}

bool LayoutContainer::showOuterPadding(bool padding)
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
		{
			count++;
		}
	}
	
	return count;
}

