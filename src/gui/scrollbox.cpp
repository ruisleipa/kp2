#include "scrollbox.hpp"

#include "freecontainer.hpp"
#include "verticalscrollbar.hpp"
#include "horizontalscrollbar.hpp"
#include "container.hpp"

#include <sstream>

void ScrollBox::addWidget(Widget& widget, const std::string width,
const std::string height)
{
	std::cout << &widget << std::endl;
	
	Container& container = dynamic_cast<Container&>(loader.getRootWidget());
	
	FreeContainer& viewPort = dynamic_cast<FreeContainer&>(container.getChildByName("viewPort"));
	
	if(currentWidget)
	{
		viewPort.removeWidget(*currentWidget);
	}
	
	viewPort.addWidget(widget, "0px", "0px", width, height);
	
	currentWidget = &widget;
	
	updateViewPosition();
}

void ScrollBox::handleEvent(Event* event)
{
	Widget::handleEvent(event);
	
	Container& container = dynamic_cast<Container&>(loader.getRootWidget());
	
	updateViewPosition();

	container.handleEvent(event);
}

Vector2D ScrollBox::getWidgetPosition(Widget* widget, Vector2D ourSize)
{
	return Vector2D(0, 0);
}

Vector2D ScrollBox::getWidgetSize(Widget* widget, Vector2D ourSize)
{
	return ourSize;
}

void ScrollBox::updateViewPosition()
{
	Container& container = dynamic_cast<Container&>(loader.getRootWidget());
	VerticalScrollBar& vertical = dynamic_cast<VerticalScrollBar&>(container.getChildByName("verticalScroll"));
	HorizontalScrollBar& horizontal = dynamic_cast<HorizontalScrollBar&>(container.getChildByName("horizontalScroll"));
	FreeContainer& viewPort = dynamic_cast<FreeContainer&>(container.getChildByName("viewPort"));
	
	Vector2D size;
	
	if(currentWidget)
	{
		size = currentWidget->getLatestSize() - Vector2D(1, 1);
		
		std::stringstream left;
		left << "-" << horizontal.getValue() << "px";

		std::stringstream top;
		top << "-" << vertical.getValue() << "px";

		viewPort.setWidgetPosition(*currentWidget, left.str(), top.str());
	}
	
	vertical.setRange(0, size.getY());
	horizontal.setRange(0, size.getX());
	
	Vector2D viewPortSize = viewPort.getLatestSize();
	
	bool scrollHorizontal = size.getX() > viewPortSize.getX();
	bool scrollVertical = size.getY() > viewPortSize.getY();
	
	horizontal.setVisible(scrollHorizontal);
	vertical.setVisible(scrollVertical);
	
	Widget& corner = dynamic_cast<Widget&>(container.getChildByName("corner"));
	corner.setVisible(scrollVertical && scrollHorizontal);
	
	vertical.setThumbSize(viewPortSize.getY());
	horizontal.setThumbSize(viewPortSize.getX());
}

ScrollBox::ScrollBox():
	loader("data/widgets/scrollbox.txt"),
	currentWidget(0)
{
	Container::addWidget(&loader.getRootWidget());
}
