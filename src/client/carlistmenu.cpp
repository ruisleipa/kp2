#include "carlistmenu.hpp"

#include <iostream>
#include <sstream>

#include "ui.hpp"
#include "graphics/texture.hpp"
#include "utils/string.hpp"
#include "connection.hpp"

CarListMenu::CarListMenu(Connection& connection):
	connection(connection)
{
	connection.addEventHandler(std::tr1::bind(&CarListMenu::onConnectionEvent,this,std::tr1::placeholders::_1));

	carList.setChangeHandler(std::tr1::bind(&CarListMenu::carlistChange,this));
	
	sellButton.setText("Myy auto");
	sellButton.setClickHandler(std::tr1::bind(&CarListMenu::sellClick,this));
	sellButton.autoSize();
	selectButton.setText("Valitse käyttöautoksi");
	selectButton.setClickHandler(std::tr1::bind(&CarListMenu::selectClick,this));
	selectButton.autoSize();
	
	addWidget(mainContainer);
	
	mainContainer.setFactorSize(Vector2D(1,1));
	
	mainContainer.addWidget(carList);
	mainContainer.addWidget(infoContainer);
	
	carList.setFluid(true);	
	infoContainer.setFluid(true);	
	
	infoContainer.addWidget(vehicleInfo);
	infoContainer.addWidget(sellButton);
	infoContainer.addWidget(selectButton);
	infoContainer.showOuterPadding(false);
	
	vehicleInfo.setFluid(true);
}

void CarListMenu::onConnectionEvent(Connection& connection)
{
	std::vector<Protocol::VehicleId> ids = connection.getPlayerVehicles().getKeys();	
	std::vector<Protocol::VehicleId>::iterator i;	
	
	carList.clearItems();
	
	for(i = ids.begin(); i != ids.end(); ++i)
	{
		Protocol::Vehicle vehicle = connection.getPlayerVehicles().getItem(*i);
		
		carList.addItem(vehicle.name, *i);
	}	
}

void CarListMenu::carlistChange()
{
	vehicleInfo.showVehicle(connection, carList.getCurrentItemTag());
}

void CarListMenu::sellClick()
{

}

void CarListMenu::selectClick()
{
	connection.setActiveVehicleId(carList.getCurrentItemTag());
}

