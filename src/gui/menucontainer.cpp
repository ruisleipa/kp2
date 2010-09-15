#include "menucontainer.hpp"

#include <cstdlib>

void MenuContainer::showOnlyWidget(const std::string& tag)
{
	Container::showOnlyWidget(tag);
	
	changeBackground();
	
	backgroundFront.setVisible(true);
	backgroundBack.setVisible(true);
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

MenuContainer::MenuContainer(TextureCollection& backgroundtextures):
	backgroundtextures(backgroundtextures),
	backgroundIndex(0)
{
	backgroundFront.setTexture(backgroundtextures.getTexture(getRandomTextureIndex()));
	backgroundFront.setSize(Vector2D(1,1));
	
	backgroundBack.setSize(Vector2D(1,1));
	
	addWidget(backgroundFront);
	addWidget(backgroundBack);
}

int MenuContainer::getRandomTextureIndex()
{
	int i=rand()%(backgroundtextures.getTextureCount()-1);
	
	if(i == backgroundIndex)
		i++;
		
	return i;
}