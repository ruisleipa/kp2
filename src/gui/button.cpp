#include "button.hpp"

#include "utils/string.hpp"
#include "debug/assert.hpp"

#include <GL/gl.h>

void Button::onMouseDown(MouseEvent event)
{
	if(event.isButtonDown(MouseEvent::LEFT) || event.isButtonDown(MouseEvent::RIGHT))
	{
		ActiveTextWidget::onMouseDown(event);
		
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

