#include "select.hpp"

#include "utils/string.hpp"
#include "debug/assert.hpp"
#include "graphics/scissor.hpp"

void Select::handleEvent(Event* event)
{
	ActiveTextWidget::handleEvent(event);
	
	if(dynamic_cast<MouseDownEvent*>(event))
		handleMouseDownEvent(dynamic_cast<MouseDownEvent*>(event));
}

void Select::handleMouseDownEvent(MouseDownEvent* event)
{
	if(selectedIndex == -1)
		return;

	if(event->isButtonDown(MouseEvent::LEFT) || event->isButtonDown(MouseEvent::WHEELDOWN))
	{
		if(selectedIndex==items.size()-1)
			setIndex(0);
		else
			setIndex(getIndex()+1);
	}
		
	if(event->isButtonDown(MouseEvent::RIGHT) || event->isButtonDown(MouseEvent::WHEELUP))
	{
		if(selectedIndex==0)
			setIndex(items.size()-1);
		else
			setIndex(getIndex()-1);
	}
}

void Select::setChangeHandler(std::tr1::function<void()> handler)
{
	changeHandler = handler;
}

void Select::addItem(std::string item)
{
	if(selectedIndex == -1)
		setIndex(0);
		
	items.push_back(convertToWideString(item));
}

void Select::clearItems()
{
	items.clear();
	selectedIndex=-1;
}

int Select::getIndex()
{
	return selectedIndex;
}

void Select::setIndex(int index)
{
	if(index >= 0 && index < items.size())
	{
		selectedIndex=index;
		
		setText(items[selectedIndex]);
		autoSize();
		
		if(changeHandler)
			changeHandler();
	}
}

Select::Select():
	selectedIndex(-1)
{
	setFont(Font("Select"));
	setActiveFont(Font("Select.active"));
}

