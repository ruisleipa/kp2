#include "label.hpp"

void Label::onDraw(Graphics& graphics)
{
	getFont().drawWrapped(getWideText(),getScreenPosition(),getSize());
}

Label::Label()
{
	setFont(Font("Label"));
}
