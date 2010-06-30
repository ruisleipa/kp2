#include "label.hpp"

void Label::onDraw(Graphics& graphics)
{
	getFont().draw(getWideText(),getScreenPosition());
}

Label::Label()
{
	setFont(Font("Label"));
}
