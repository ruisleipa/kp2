#include "button.hpp"

#include "shared/string.hpp"
#include "assert.hpp"
#include "ui.hpp"

#include <GL/gl.h>

void Button::onClick()
{

}

void Button::mouseDown(MouseEvent event)
{
	if(event.isButtonDown(MouseEvent::LEFT) || event.isButtonDown(MouseEvent::RIGHT))
	{
		ActiveTextWidget::mouseDown(event);
		
		onClick();
	}
}

Button::Button()
{
	setFont(Ui::getInstance().getFont("Button"));
	setActiveFont(Ui::getInstance().getFont("Button.active"));
}

