#include "localgamemenu.hpp"

#include "gui/label.hpp"
#include "gui/button.hpp"

LocalGameMenu::LocalGameMenu(MenuContainer& menuContainer):
	menuContainer(menuContainer),
	loader("data/ui/localgamemenu.ui")
{
	addWidget(loader.getRootWidget(), "0px", "0px", "100%", "100%");

	dynamic_cast<Label&>(getChildByName("title")).setFont(Font("title"));
	
	dynamic_cast<Button&>(getChildByName("newGameButton")).setClickHandler(std::tr1::bind(&LocalGameMenu::newClickHandler,this));	
	dynamic_cast<Button&>(getChildByName("backButton")).setClickHandler(std::tr1::bind(&LocalGameMenu::backClickHandler,this));
}

void LocalGameMenu::backClickHandler()
{
	menuContainer.showOnlyWidget("mainmenu");
}

void LocalGameMenu::newClickHandler()
{
	menuContainer.showOnlyWidget("newlocalgamemenu");
}

