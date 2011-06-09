#include "menucontainer.hpp"

#include <cstdlib>

void MenuContainer::addWidget(const std::string& name, Widget& widget)
{
	widget.setName(name);
	
	FreeContainer::addWidget(widget, "0px", "0px", "100%", "100%");
}

void MenuContainer::showOnlyWidget(const std::string& tag)
{
	Container::showOnlyWidget(tag);
	
	changeBackground();
	
	backgroundFront.setVisible(true);
	backgroundBack.setVisible(true);
}

void MenuContainer::handleEvent(Event* event)
{
	if(dynamic_cast<DrawEvent*>(event))
		handleDrawEvent(dynamic_cast<DrawEvent*>(event));
		
	Container::handleEvent(event);
}

void MenuContainer::handleDrawEvent(DrawEvent* event)
{
	float alpha=backgroundChangeTimer.getSeconds()*10.0;
	if(alpha > 1.0)
		alpha = 1.0;
	
	backgroundBack.setColor(Color(1,1,1,1.0-alpha));
	backgroundFront.setColor(Color(1,1,1,1.0));
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
	
	backgroundBack.setFill(true);
	backgroundFront.setFill(true);
	
	FreeContainer::addWidget(backgroundFront, "0px", "0px", "100%", "100%");
	FreeContainer::addWidget(backgroundBack, "0px", "0px", "100%", "100%");
}

int MenuContainer::getRandomTextureIndex()
{
	int i=rand()%(backgroundtextures.getTextureCount()-1);
	
	if(i == backgroundIndex)
		i++;
		
	return i;
}
