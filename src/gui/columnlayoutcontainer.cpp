#include "columnlayoutcontainer.hpp"

#include "ui.hpp"

void ColumnLayoutContainer::onDraw(Window& window)
{
	int visible_widgets=0;

	for(int i=0;i<getWidgetCount();i++)
	{
		Widget* widget=getWidget(i);
		
		if(!widget)
			continue;
			
		if(widget->getVisible())
		{
			visible_widgets++;
		}
	}
	
	if(visible_widgets == 0)
	{
		return;
	}
	
	Vector2D widgetsize;
	widgetsize.setX(getSize().getX()/visible_widgets-PADDING*(visible_widgets+1)/visible_widgets);
	widgetsize.setY(getSize().getY()-PADDING*2);
	
	int visible_index=0;
	
	for(int i=0;i<getWidgetCount();i++)
	{
		Widget* widget=getWidget(i);
		
		if(!widget)
			continue;
	
		if(widget->getVisible())
		{
			Vector2D pos;
			pos.setY(PADDING);
			pos.setX(PADDING*(visible_index+1)+widgetsize.getX()*visible_index);	
			
			widget->setPosition(pos);
			widget->setSize(widgetsize);
			
			visible_index++;
		}
	}	
}
