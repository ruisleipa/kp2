#include "label.hpp"

#include "ui.hpp"

void Label::draw()
{
	if(getFont())
		getFont()->draw(getWideText(),getPosition());
}

Label::Label()
{
	setFont(Ui::getInstance().getFont("Label"));
}
