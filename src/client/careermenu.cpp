#include "careermenu.hpp"

#include "gui/label.hpp"
#include "gui/button.hpp"
#include "gui/image.hpp"

CareerMenu::CareerMenu(TextureCollection& sidebartextures,Container& topLevelGameMenus,Connection& connection):
	connection(connection),
	topLevelGameMenus(topLevelGameMenus),
	loader("data/ui/careermenu.ui")
{
	connection.addEventHandler(std::tr1::bind(&CareerMenu::onConnectionEvent,this,std::tr1::placeholders::_1));
	
	addWidget(loader.getRootWidget(), "0px", "0px", "20%", "100%");
	
	addWidget(topLevelGameMenus, "20%", "0px", "80%", "100%");
	
	dynamic_cast<Image&>(getChildByName("background")).setTexture(sidebartextures.getTexture("background"));
	dynamic_cast<Image&>(getChildByName("background")).setStretched(true);

	dynamic_cast<Button&>(getChildByName("garageButton")).setClickHandler(std::tr1::bind(&CareerMenu::garageButtonClick,this));
	dynamic_cast<Button&>(getChildByName("tuningButton")).setClickHandler(std::tr1::bind(&CareerMenu::tuningButtonClick,this));
	dynamic_cast<Button&>(getChildByName("financeButton")).setClickHandler(std::tr1::bind(&CareerMenu::tuningButtonClick,this));
	dynamic_cast<Button&>(getChildByName("raceButton")).setClickHandler(std::tr1::bind(&CareerMenu::raceButtonClick,this));

}

void CareerMenu::onConnectionEvent(Connection& connection)
{
	std::stringstream ss;
	
	const Protocol::PlayerInfo& playerInfo = connection.getPlayerInfo();
	
	ss<<playerInfo.name<<std::endl;
	ss<<playerInfo.money<<" €";

	dynamic_cast<Label&>(getChildByName("infoLabel")).setText(ss.str());
}

void CareerMenu::garageButtonClick()
{
	topLevelGameMenus.showOnlyWidget("garage");
}

void CareerMenu::tuningButtonClick()
{
	topLevelGameMenus.showOnlyWidget("tuning");
}

void CareerMenu::financeButtonClick()
{
	topLevelGameMenus.showOnlyWidget("finance");
}

void CareerMenu::raceButtonClick()
{
	connection.startRace();
}

