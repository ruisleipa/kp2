#include "tabbedmenucontainer.hpp"

void TabbedMenuContainer::addMenu(std::string name,Menu& menu)
{
	MenuContainer::addMenu(name,menu);
}

TabbedMenuContainer::TabbedMenuContainer(TextureCollection& backgroundtextures):
	MenuContainer(backgroundtextures)
{

}
