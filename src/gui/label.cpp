#include "label.hpp"

void Label::handleEvent(Event* event)
{
	if(dynamic_cast<DrawEvent*>(event))
		handleDrawEvent(dynamic_cast<DrawEvent*>(event));
		
	TextWidget::handleEvent(event);
}

void Label::handleDrawEvent(DrawEvent* event)
{
	getFont().drawWrapped(getWideText(),event->getAreaPosition(),event->getAreaSize());
}

Label::Label()
{
	setFont(Font("Label"));
}
