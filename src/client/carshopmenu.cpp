#include "carshopmenu.hpp"

#include <sstream>

#include "gui/label.hpp"
#include "gui/button.hpp"
#include "gui/image.hpp"
#include "gui/field.hpp"
#include "gui/listbox.hpp"

#include "utils/string.hpp"
#include "connection.hpp"

CarShopMenu::CarShopMenu(Connection& connection):
	connection(connection),
	loader("data/ui/carshopmenu.ui")
{
	addWidget(loader.getRootWidget(), "0px", "0px", "100%", "100%");
	
	connection.addEventHandler(std::tr1::bind(&CarShopMenu::onConnectionEvent,this,std::tr1::placeholders::_1));
	
	dynamic_cast<Listbox&>(getChildByName("carList")).setChangeHandler(std::tr1::bind(&CarShopMenu::carlistChange,this));
	dynamic_cast<Button&>(getChildByName("buyButton")).setClickHandler(std::tr1::bind(&CarShopMenu::buyClick,this));
}

void CarShopMenu::onConnectionEvent(Connection& connection)
{
	dynamic_cast<Listbox&>(getChildByName("carList")).clearItems();

	std::vector<std::string> ids = connection.getShopVehicles().getKeys();
	
	for(size_t i = 0; i < ids.size(); ++i)
	{
		Protocol::ShopVehicle vehicle = connection.getShopVehicles().getItem(ids[i]);
		
		dynamic_cast<Listbox&>(getChildByName("carList")).addItem(vehicle.name, i);
	}
}

void CarShopMenu::carlistChange()
{
	std::vector<std::string> ids = connection.getShopVehicles().getKeys();
	
	Protocol::ShopVehicle vehicle = connection.getShopVehicles().getItem(ids[dynamic_cast<Listbox&>(getChildByName("carList")).getCurrentItemTag()]);
	
	dynamic_cast<Label&>(getChildByName("carName")).setText(vehicle.name);
		
	std::string image = "gamedata/vehicleimages/";
	image += vehicle.imageName;
	dynamic_cast<Image&>(getChildByName("carImage")).setTexture(Texture(image));
	
	std::stringstream ss;
	
	ss << vehicle.info << "\n" << "\n";
	ss << "Vuosimalli: " << vehicle.year << std::endl;
	ss << "Korin paino: " << vehicle.chassisWeight << std::endl;
	ss << "Hinta: " << vehicle.price << std::endl;
	
	dynamic_cast<Label&>(getChildByName("carInfo")).setText(ss.str());
}

void CarShopMenu::buyClick()
{
	std::vector<std::string> ids = connection.getShopVehicles().getKeys();
	
	if(dynamic_cast<Listbox&>(getChildByName("carList")).getCurrentItemTag() != -1)
		connection.buyVehicle(ids[dynamic_cast<Listbox&>(getChildByName("carList")).getCurrentItemTag()]);
}

