#include "button.hpp"

#include "utils/string.hpp"
#include "debug/assert.hpp"

#include <GL/gl.h>

void Button::handleEvent(Event* event)
{
	ActiveTextWidget::handleEvent(event);

	if(dynamic_cast<MouseDownEvent*>(event))
		handleMouseDownEvent(dynamic_cast<MouseDownEvent*>(event));
}

void Button::handleMouseDownEvent(MouseDownEvent* event)
{
	if(event->isButtonDown(MouseEvent::LEFT))
	{
		if(clickHandler)
			clickHandler();
	}
}

void Button::setClickHandler(std::tr1::function<void()> handler)
{
	clickHandler=handler;
}

Button::Button()
{
	setFont(Font("Button"));
	setActiveFont(Font("Button.active"));
}

