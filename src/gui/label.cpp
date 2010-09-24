#include "label.hpp"

void Label::onDraw(DrawEvent event)
{
	getFont().drawWrapped(getWideText(),event.getAreaPosition(),event.getAreaSize());
}

Label::Label()
{
	setFont(Font("Label"));
}
