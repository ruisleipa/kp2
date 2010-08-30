#include "menu.hpp"

Menu::Menu()
{
	setSize(Vector2D(1,1));
}

MenuContainer* Menu::getMenuContainer()
{
	return menuContainer;
}

void Menu::setMenuContainer(MenuContainer* menuContainer)
{
	this->menuContainer = menuContainer;
}
