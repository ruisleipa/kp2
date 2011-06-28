#include "carlistmenu.hpp"

#include <iostream>

#include "connection.hpp"
#include "gui/button.hpp"
#include "gui/layoutcontainer.hpp"

CarListMenu::CarListMenu(Connection& connection, Container& parent):
	Menu("data/ui/carlistmenu.ui"),
	connection(connection),
	parent(parent)
{
	connection.addEventHandler(std::tr1::bind(&CarListMenu::onConnectionEvent,this,std::tr1::placeholders::_1));

	getChildByName<Button>("sellButton").setClickHandler(std::tr1::bind(&CarListMenu::sellClick,this));
	getChildByName<Button>("selectButton").setClickHandler(std::tr1::bind(&CarListMenu::selectClick,this));
	getChildByName<Button>("backButton").setClickHandler(std::tr1::bind(&Container::showOnlyWidget, &parent, "gamemainmenu"));
	
	for(int i = 0; i < 4; i++)
		getChildByName<LayoutContainer>("firstColumn").addWidget(buttons[i], "100%", "25%");
		
	for(int i = 4; i < 8; i++)
		getChildByName<LayoutContainer>("secondColumn").addWidget(buttons[i], "100%", "25%");
}

void CarListMenu::onConnectionEvent(Connection& connection)
{
	std::vector<Protocol::VehicleId> ids = connection.getPlayerVehicles().getKeys();
	std::vector<Protocol::VehicleId>::iterator i;
	
	for(int i = 0; i < 8; i++)
	{
		buttons[i].setVisible(false);
		buttons[i].setClickHandler(0);
	}
	
	int buttonIndex = 0;
	
	for(i = ids.begin(); i != ids.end(); ++i)
	{
		Protocol::Vehicle vehicle = connection.getPlayerVehicles().getItem(*i);
		
		buttons[buttonIndex].setVisible(true);
		buttons[buttonIndex].showVehicle(connection, *i);
		buttons[buttonIndex].setClickHandler(std::tr1::bind(&CarListMenu::vehicleClick, this, *i));
		
		buttonIndex++;
		
		if(buttonIndex == 8)
			return;
	}
}

void CarListMenu::sellClick()
{

}

void CarListMenu::selectClick()
{

}

void CarListMenu::vehicleClick(int id)
{
	connection.setActiveVehicleId(id);
	parent.showOnlyWidget("gamemainmenu");
}
