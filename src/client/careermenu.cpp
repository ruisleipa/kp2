#include "careermenu.hpp"

#include "gui/label.hpp"
#include "gui/button.hpp"
#include "gui/image.hpp"

CareerMenu::CareerMenu(TextureCollection& sidebartextures,Container& gameMenus,Connection& connection):
	Menu("data/ui/careermenu.ui"),
	connection(connection),
	gameMenus(gameMenus)
{
	connection.addEventHandler(std::tr1::bind(&CareerMenu::onConnectionEvent,this,std::tr1::placeholders::_1));
	
	getChildByName<FreeContainer>("menucontainer").addWidget(gameMenus, "0px", "0px", "100%", "100%");
}

void CareerMenu::onConnectionEvent(Connection& connection)
{
	const Protocol::PlayerInfo& playerInfo = connection.getPlayerInfo();
	
	getChildByName<Label>("nameLabel").setText(playerInfo.name);
	
	std::stringstream moneyString;
	
	moneyString << "Rahaa:" << playerInfo.money;
	
	getChildByName<Label>("moneyLabel").setText(moneyString.str());
	
	getChildByName<Label>("seriesLabel").setText("3. divisioona");
}


