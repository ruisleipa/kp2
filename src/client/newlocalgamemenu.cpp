#include "newlocalgamemenu.hpp"

#include <iostream>

#include "ui.hpp"
#include "utils/string.hpp"
#include "gui/label.hpp"
#include "gui/select.hpp"
#include "gui/button.hpp"
#include "gui/image.hpp"
#include "gui/field.hpp"

NewLocalGameMenu::NewLocalGameMenu(MenuContainer& menuContainer, Connection& connection):
	menuContainer(menuContainer),
	connection(connection),
	loader("data/ui/newlocalgamemenu.ui")
{
	addWidget(loader.getRootWidget(), "0px", "0px", "100%", "100%");

	dynamic_cast<Label&>(getChildByName("title")).setFont(Font("title"));
	
	dynamic_cast<Select&>(getChildByName("difficultySelect")).addItem("helppo");
	dynamic_cast<Select&>(getChildByName("difficultySelect")).addItem("normaali");
	dynamic_cast<Select&>(getChildByName("difficultySelect")).addItem("vaikea");

	dynamic_cast<Button&>(getChildByName("backButton")).setClickHandler(std::tr1::bind(&NewLocalGameMenu::backClickHandler,this));
	dynamic_cast<Button&>(getChildByName("startButton")).setClickHandler(std::tr1::bind(&NewLocalGameMenu::startClickHandler,this));
}

void NewLocalGameMenu::onShow()
{
	dynamic_cast<Field&>(getChildByName("nameField")).setText("");
	dynamic_cast<Select&>(getChildByName("difficultySelect")).setIndex(1);
}

void NewLocalGameMenu::backClickHandler()
{
	menuContainer.showOnlyWidget("localgamemenu");
}

void NewLocalGameMenu::startClickHandler()
{
	if(connection.startLocalServer())
	{
		menuContainer.showOnlyWidget("careermenu");
		
		connection.setName(dynamic_cast<Field&>(getChildByName("nameField")).getText());
	}
}

