#include "menu.hpp"

MenuContainer* Menu::getMenuContainer()
{
	return menuContainer;
}

void Menu::setMenuContainer(MenuContainer* menuContainer)
{
	this->menuContainer = menuContainer;
}
