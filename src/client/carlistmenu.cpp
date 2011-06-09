#include "carlistmenu.hpp"

#include <iostream>
#include <sstream>

#include "ui.hpp"
#include "graphics/texture.hpp"
#include "utils/string.hpp"
#include "connection.hpp"
#include "gui/label.hpp"
#include "gui/button.hpp"
#include "gui/listbox.hpp"
#include "gui/rowlayoutcontainer.hpp"
#include "gui/columnlayoutcontainer.hpp"
#include "playervehiclewidget.hpp"

CarListMenu::CarListMenu(Connection& connection):
	connection(connection),
	loader("data/ui/carlistmenu.ui")
{
	addWidget(loader.getRootWidget(), "0px", "0px", "100%", "100%");
	
	connection.addEventHandler(std::tr1::bind(&CarListMenu::onConnectionEvent,this,std::tr1::placeholders::_1));

	dynamic_cast<Listbox&>(getChildByName("carList")).setChangeHandler(std::tr1::bind(&CarListMenu::carlistChange,this));
	
	dynamic_cast<Button&>(getChildByName("sellButton")).setClickHandler(std::tr1::bind(&CarListMenu::sellClick,this));
	dynamic_cast<Button&>(getChildByName("selectButton")).setClickHandler(std::tr1::bind(&CarListMenu::selectClick,this));
}

void CarListMenu::onConnectionEvent(Connection& connection)
{
	std::vector<Protocol::VehicleId> ids = connection.getPlayerVehicles().getKeys();	
	std::vector<Protocol::VehicleId>::iterator i;	
	
	dynamic_cast<Listbox&>(getChildByName("carList")).clearItems();
	
	for(i = ids.begin(); i != ids.end(); ++i)
	{
		Protocol::Vehicle vehicle = connection.getPlayerVehicles().getItem(*i);
		
		dynamic_cast<Listbox&>(getChildByName("carList")).addItem(vehicle.name, *i);
	}	
}

void CarListMenu::carlistChange()
{
	dynamic_cast<PlayerVehicleWidget&>(getChildByName("vehicleInfo")).showVehicle(connection, dynamic_cast<Listbox&>(getChildByName("carList")).getCurrentItemTag());
}

void CarListMenu::sellClick()
{

}

void CarListMenu::selectClick()
{
	connection.setActiveVehicleId(dynamic_cast<Listbox&>(getChildByName("carList")).getCurrentItemTag());
}

