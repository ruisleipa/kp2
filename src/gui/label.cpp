#include "label.hpp"

void Label::onDraw(Window& window)
{
	getFont().drawWrapped(window,getWideText(),getScreenPosition(),getSize());
}

Label::Label()
{
	setFont(Font("Label"));
}
