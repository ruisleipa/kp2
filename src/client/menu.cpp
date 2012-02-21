#include "menu.hpp"

#include <QStyleOption>
#include <QPainter>

Menu::Menu(QWidget *parent) :
	QWidget(parent)
{
  
}

void Menu::paintEvent(QPaintEvent *)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
