#include "label.hpp"

void Label::draw(Graphics& graphics)
{
	getFont().draw(getWideText(),getPosition());
}

Label::Label()
{
	setFont(Font("Label"));
}
