#include "mainmenu.hpp"

#include "gui/image.hpp"
#include "gui/button.hpp"

MainMenu::MainMenu(MenuContainer& menuContainer, TextureCollection& textureCollection):
	menuContainer(menuContainer),
	loader("data/ui/mainmenu.ui")
{
	addWidget(loader.getRootWidget(), "0px", "0px", "100%", "100%");
	
	dynamic_cast<Image&>(getChildByName("title")).setTexture(textureCollection.getTexture("title"));
	
	dynamic_cast<Button&>(getChildByName("remoteGameButton")).setClickHandler(std::tr1::bind(&MainMenu::remotegameClickHandler,this));	
	dynamic_cast<Button&>(getChildByName("localgameButton")).setClickHandler(std::tr1::bind(&MainMenu::localgameClickHandler,this));
	dynamic_cast<Button&>(getChildByName("settingsButton")).setClickHandler(std::tr1::bind(&MainMenu::settingsClickHandler,this));	
	dynamic_cast<Button&>(getChildByName("quitButton")).setClickHandler(std::tr1::bind(&MainMenu::quitClickHandler,this));
}

void MainMenu::remotegameClickHandler()
{
	menuContainer.showOnlyWidget("remotegamemenu");
}

void MainMenu::localgameClickHandler()
{
	menuContainer.showOnlyWidget("localgamemenu");
}

void MainMenu::aboutClickHandler()
{

}

void MainMenu::settingsClickHandler()
{
	menuContainer.showOnlyWidget("settingsmenu");
}

void MainMenu::quitClickHandler()
{
	//throw ExitException();
}


