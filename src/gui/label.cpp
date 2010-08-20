#include "label.hpp"

void Label::onDraw(Window& window)
{
	getFont().drawWrapped(getWideText(),getAbsolutePosition(),getSize());
}

Label::Label()
{
	setFont(Font("Label"));
}
