#include "carshopmenu.hpp"

#include <iostream>
#include <sstream>

#include "ui.hpp"
#include "utils/string.hpp"
#include "connection.hpp"

CarShopMenu::CarShopMenu(Connection& connection):
	connection(connection)
{
	connection.addEventHandler(std::tr1::bind(&CarShopMenu::onConnectionEvent,this,std::tr1::placeholders::_1));
	
	carList.setFont(Font("small"));
	carList.setChangeHandler(std::tr1::bind(&CarShopMenu::carlistChange,this));
		
	carInfo.setFont(Font("small"));	
	
	buyButton.setText("Osta auto");
	buyButton.autoSize();
	buyButton.setClickHandler(std::tr1::bind(&CarShopMenu::buyClick,this));
				
	addWidget(mainContainer);
	
	mainContainer.setFactorSize(Vector2D(1,1));
	
	mainContainer.addWidget(carList);
	mainContainer.addWidget(infoContainer);
	
	carList.setFluid(true);	
	infoContainer.setFluid(true);	
	
	infoContainer.addWidget(titleContainer);
	infoContainer.addWidget(carInfo);
	infoContainer.addWidget(buyButton);
	infoContainer.showOuterPadding(false);
	
	titleContainer.setFactorSize(Vector2D(0,0.25));
	carInfo.setFluid(true);	
		
	titleContainer.addWidget(carName);
	titleContainer.addWidget(carImage);
	titleContainer.showOuterPadding(false);
	
	carName.setFluid(true);	
	carImage.setFluid(true);	
	
}

void CarShopMenu::onConnectionEvent(Connection& connection)
{
	const Protocol::ShopVehicles& shopVehicles = connection.getShopVehicles();
	
	carList.clearItems();
	
	for(size_t i = 0; i < shopVehicles.getItemCount(); ++i)
	{
		Protocol::ShopVehicle vehicle =  shopVehicles.getItem(i);
		
		carList.addItem(vehicle.name, i);
	}	
}

void CarShopMenu::carlistChange()
{
	const Protocol::ShopVehicles& shopVehicles = connection.getShopVehicles();

	Protocol::ShopVehicle vehicle = shopVehicles.getItem(carList.getIndex());
	
	carName.setText(vehicle.name);
		
	std::string image = "gamedata/vehicleimages/";
	image += vehicle.imageName;
	carImage.setTexture(Texture(image));
	
	std::stringstream ss;
	
	ss << vehicle.info << "\n" << "\n";
	ss << "Vuosimalli: " << vehicle.year << std::endl;
	ss << "Korin paino: " << vehicle.chassisWeight << std::endl;
	ss << "Hinta: " << vehicle.price << std::endl;
	
	carInfo.setText(ss.str());
}

void CarShopMenu::buyClick()
{
	const Protocol::ShopVehicles& shopVehicles = connection.getShopVehicles();
	
	if(carList.getCurrentItemTag() != -1)
	{
		Protocol::ShopVehicle vehicle = shopVehicles.getItem(carList.getCurrentItemTag());
	
		connection.buyVehicle(vehicle.id);
	}
}

