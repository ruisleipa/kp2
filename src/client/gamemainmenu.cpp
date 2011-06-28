#include "gamemainmenu.hpp"

#include <sstream>

#include "gui/button.hpp"
#include "gui/image.hpp"
#include "gui/label.hpp"

GameMainMenu::GameMainMenu(Connection& connection, Container& parent):
	Menu("data/ui/gamemainmenu.ui"),
	connection(connection)
{
	connection.addEventHandler(std::tr1::bind(&GameMainMenu::onConnectionEvent,this,std::tr1::placeholders::_1));

	getChildByName<Button>("carShopButton").setClickHandler(std::tr1::bind(&Container::showOnlyWidget, &parent, "carshopmenu"));
	getChildByName<Button>("carListButton").setClickHandler(std::tr1::bind(&Container::showOnlyWidget, &parent, "carlistmenu"));
	getChildByName<Button>("installPartsButton").setClickHandler(std::tr1::bind(&Container::showOnlyWidget, &parent, "installpartsmenu"));
	getChildByName<Button>("testButton").setClickHandler(std::tr1::bind(&Connection::startTestRun, &connection));
}

void GameMainMenu::onConnectionEvent(Connection& connection)
{
	int vehicleId = connection.getActiveVehicleId();

	if(vehicleId == 0)
	{
		getChildByName<Image>("vehicleImage").setTexture(Texture());
		getChildByName<Label>("vehicleName").setText("Ei käyttöautoa");
		getChildByName<Label>("vehicleInfo").setText("");
		
		return;
	}
	
	const Protocol::Vehicle& vehicle = connection.getPlayerVehicles().getItem(vehicleId);

	std::string file = "gamedata/vehicleimages/" + vehicle.imageName;
	getChildByName<Image>("vehicleImage").setTexture(Texture(file));
	
	std::stringstream name;
	
	name << vehicle.name << " vm. " << vehicle.year << "\n";
	
	getChildByName<Label>("vehicleName").setText(name.str());
	
	std::stringstream info;
	
	info << "Tekniikka: jotain tekniikasta" << "\n";
	info << "Paino: " << vehicle.totalWeight << " kg\n";
	info << "Jotain: jotain" << "\n";
	
	getChildByName<Label>("vehicleInfo").setText(info.str());
}
