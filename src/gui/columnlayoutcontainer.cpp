#include "columnlayoutcontainer.hpp"

const float PADDING=0.01;

void ColumnLayoutContainer::onDraw(Window& window)
{
	int visibleChildrenCount=0;

	for(int i=0;i<getChildCount();i++)
	{
		Widget* child=getChild(i);
		
		if(!child)
			continue;
			
		if(child->getVisible())
		{
			visibleChildrenCount++;
		}
	}
	
	if(visibleChildrenCount == 0)
	{
		return;
	}
	
	Vector2D childSize;
	childSize.setX(getSize().getX()/visibleChildrenCount-PADDING*(visibleChildrenCount+1)/visibleChildrenCount);
	childSize.setY(getSize().getY()-PADDING*2);
	
	int visibleChildrenIndex=0;
	
	for(int i=0;i<getChildCount();i++)
	{
		Widget* child=getChild(i);
		
		if(!child)
			continue;
	
		if(child->getVisible())
		{
			Vector2D pos;
			pos.setY(PADDING);
			pos.setX(PADDING*(visibleChildrenIndex+1)+childSize.getX()*visibleChildrenIndex);	
			
			child->setPosition(pos);
			child->setSize(childSize);
			
			visibleChildrenIndex++;
		}
	}	
}
