#include "simplemenucontainer.hpp"

void SimpleMenuContainer::addMenu(std::string name,Menu& menu)
{
	MenuContainer::addMenu(name,menu);
	
	menu.setPosition(Vector2D(0,0));
	menu.setSize(Vector2D(1,1));
}

SimpleMenuContainer::SimpleMenuContainer(TextureCollection& backgroundtextures):
	MenuContainer(backgroundtextures)
{

}
