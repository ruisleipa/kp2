#include "carshopmenu.hpp"

#include <sstream>

#include "gui/label.hpp"
#include "gui/button.hpp"
#include "gui/image.hpp"
#include "gui/field.hpp"
#include "gui/listbox.hpp"

#include "utils/string.hpp"
#include "connection.hpp"

CarShopMenu::CarShopMenu(Connection& connection, Container& parent):
	connection(connection),
	loader("data/ui/carshopmenu.ui")
{
	addWidget(loader.getRootWidget(), "0px", "0px", "100%", "100%");
	
	connection.addEventHandler(std::tr1::bind(&CarShopMenu::onConnectionEvent,this,std::tr1::placeholders::_1));
	
	getChildByName<Listbox>("carList").setChangeHandler(std::tr1::bind(&CarShopMenu::carlistChange,this));
	getChildByName<Button>("buyButton").setClickHandler(std::tr1::bind(&CarShopMenu::buyClick,this));
	getChildByName<Button>("backButton").setClickHandler(std::tr1::bind(&Container::showOnlyWidget, &parent, "gamemainmenu"));
}

void CarShopMenu::onConnectionEvent(Connection& connection)
{
	getChildByName<Listbox>("carList").clearItems();

	std::vector<std::string> ids = connection.getShopVehicles().getKeys();
	
	for(size_t i = 0; i < ids.size(); ++i)
	{
		Protocol::ShopVehicle vehicle = connection.getShopVehicles().getItem(ids[i]);
		
		getChildByName<Listbox>("carList").addItem(vehicle.name, i);
	}
}

void CarShopMenu::carlistChange()
{
	std::vector<std::string> ids = connection.getShopVehicles().getKeys();
	
	Protocol::ShopVehicle vehicle = connection.getShopVehicles().getItem(ids[getChildByName<Listbox>("carList").getCurrentItemTag()]);
	
	std::stringstream title;
	
	title << vehicle.name << " vm. " << vehicle.year << "\n";
	title << "Hinta: " << vehicle.price;
	
	getChildByName<Label>("carNameLabel").setText(title.str());
			
	std::string image = "gamedata/vehicleimages/";
	image += vehicle.imageName;
	getChildByName<Image>("carImage").setTexture(Texture(image));
	
	std::stringstream ss;
	
	ss << "Auton paino: " << vehicle.chassisWeight << "kg" << "\n";
	ss << "Tekniikka: " << "1.0 L, ruisku, jotain tämmöstä" << "\n";
	ss << "Voimansiirto: " << "etuveto" << "\n";
	ss << "Max. teho: " << "25 kW @ 4000 rpm" << "\n";
	ss << "Max. vääntö: " << "78 Nm @ 3000 rpm" << "\n";
	ss << "Kiihtyvyys: " << "13.5s 0-100 km/h" << "\n";
	ss << "\n" << vehicle.info << "\n";	
	
	getChildByName<Label>("carInfoLabel").setText(ss.str());
}

void CarShopMenu::buyClick()
{
	std::vector<std::string> ids = connection.getShopVehicles().getKeys();
	
	if(dynamic_cast<Listbox&>(getChildByName("carList")).getCurrentItemTag() != -1)
		connection.buyVehicle(ids[dynamic_cast<Listbox&>(getChildByName("carList")).getCurrentItemTag()]);
}

