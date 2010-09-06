#include "tabbedmenucontainer.hpp"

void TabbedMenuContainer::addMenu(std::string name,Menu& menu,std::string label)
{
	MenuContainer::addMenu(name,menu);
		
	menu.setPosition(Vector2D(0.1,0.1));
	menu.setSize(Vector2D(0.8,0.8));
}

TabbedMenuContainer::TabbedMenuContainer(TextureCollection& backgroundtextures):
	MenuContainer(backgroundtextures)
{

}
