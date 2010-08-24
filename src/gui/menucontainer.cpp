#include "menucontainer.hpp"

void MenuContainer::showMenu(std::string tag)
{
	for(int i=0; i<getChildCount(); i++)
	{
		getChild(i)->setVisible(false);
	}
	
	getChild(tag)->setVisible(true);
	backgroundFront.setVisible(true);
	backgroundBack.setVisible(true);
}

void MenuContainer::showOverlayMenu(std::string tag)
{
	getChild(tag)->setVisible(true);
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
	backgroundBack.setTexture(backgroundtextures.getTexture("image01"));
	backgroundFront.setTexture(backgroundtextures.getTexture("image00"));
	
	backgroundChangeTimer.reset();
}

MenuContainer::MenuContainer(TextureCollection& backgroundtextures):
	backgroundtextures(backgroundtextures)
{
	backgroundFront.setTexture(backgroundtextures.getTexture("image00"));
	backgroundFront.setSize(Vector2D(1,1));
	
	backgroundBack.setSize(Vector2D(1,1));
	
	addChild(backgroundFront);
	addChild(backgroundBack);
}
