#include "remotegamemenu.hpp"

#include "gui/button.hpp"
#include "gui/field.hpp"

#include "utils/string.hpp"

RemoteGameMenu::RemoteGameMenu(MenuContainer& menuContainer, Connection& connection):
	menuContainer(menuContainer),
	connection(connection),
	loader("data/ui/remotegamemenu.ui")
{
	addWidget(loader.getRootWidget(), "0px", "0px", "100%", "100%");
	
	dynamic_cast<Button&>(getChildByName("backButton")).setClickHandler(std::tr1::bind(&RemoteGameMenu::backClickHandler, this));
	dynamic_cast<Button&>(getChildByName("connectButton")).setClickHandler(std::tr1::bind(&RemoteGameMenu::connectClickHandler, this));
}

void RemoteGameMenu::onShow()
{
	dynamic_cast<Field&>(getChildByName("nameField")).setText("");
	dynamic_cast<Field&>(getChildByName("hostField")).setText("");
	dynamic_cast<Field&>(getChildByName("portField")).setText("");
}

void RemoteGameMenu::backClickHandler()
{
	menuContainer.showOnlyWidget("mainmenu");
}

void RemoteGameMenu::connectClickHandler()
{
	std::string host = dynamic_cast<Field&>(getChildByName("hostField")).getText();
	int port = convertTo<int>(dynamic_cast<Field&>(getChildByName("portField")).getText());
	std::string name = dynamic_cast<Field&>(getChildByName("nameField")).getText();

	if(connection.connect(host, port))
	{
		menuContainer.showOnlyWidget("careermenu");
		
		connection.setName(name);
	}
}

