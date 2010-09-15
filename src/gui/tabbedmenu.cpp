#include "tabbedmenu.hpp"

TabbedMenu::TabbedMenu()
{
	setSize(Vector2D(1,1));
}

void addTab(const std::string& label,Widget& widget);