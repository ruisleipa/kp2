#include "menucontainer.hpp"

#include "menu.hpp"

#include <cstdlib>

void MenuContainer::showMenu(std::string tag)
{
	std::map<std::string,Menu*>::iterator i;
		
	for(i=menus.begin(); i!=menus.end(); ++i)
	{
		(*i).second->setVisible(false);
	}

	if(menus.find(tag) != menus.end())
	{
		menus[tag]->setVisible(true);
	}
	
	changeBackground();
}

void MenuContainer::onDraw(Window& window)
{
	float alpha=backgroundChangeTimer.getSeconds()*10.0;
	if(alpha > 1.0)
		alpha = 1.0;
	
	backgroundBack.setColor(Color(1,1,1,1.0-alpha));
}

void MenuContainer::changeBackground()
{
	backgroundBack.setTexture(backgroundFront.getTexture());
	backgroundFront.setTexture(backgroundtextures.getTexture(getRandomTextureIndex()));
	
	backgroundChangeTimer.reset();
}

void MenuContainer::addMenu(std::string name,Menu& menu)
{
	Container::addChild(menu);
	
	menu.setMenuContainer(this);

	menus[name] = &menu;
}

MenuContainer::MenuContainer(TextureCollection& backgroundtextures):
	backgroundtextures(backgroundtextures),
	backgroundIndex(0)
{
	backgroundFront.setTexture(backgroundtextures.getTexture(getRandomTextureIndex()));
	backgroundFront.setSize(Vector2D(1,1));
	
	backgroundBack.setSize(Vector2D(1,1));
	
	addChild(backgroundFront);
	addChild(backgroundBack);
}

int MenuContainer::getRandomTextureIndex()
{
	int i=rand()%(backgroundtextures.getTextureCount()-1);
	
	if(i == backgroundIndex)
		i++;
		
	return i;
}
