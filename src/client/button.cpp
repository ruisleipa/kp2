#include "button.hpp"

#include "shared/string.hpp"
#include "assert.hpp"

#include <GL/gl.h>

void Button::onClick()
{

}

void Button::onMouseDown(MouseEvent event)
{
	if(event.isButtonDown(MouseEvent::LEFT) || event.isButtonDown(MouseEvent::RIGHT))
	{
		ActiveTextWidget::onMouseDown(event);
		
		onClick();
	}
}

Button::Button()
{
	setFont(Font("Button"));
	setActiveFont(Font("Button.active"));
}

