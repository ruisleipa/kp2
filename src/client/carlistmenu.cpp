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
	const Protocol::PlayerVehicles& playerVehicles = connection.getPlayerVehicles();
	
	carList.clearItems();
	
	for(size_t i = 0; i < playerVehicles.getItemCount(); ++i)
	{
		Protocol::Vehicle vehicle = playerVehicles.getItem(i);
		
		carList.addItem(vehicle.name, i);
	}	
}

void CarListMenu::carlistChange()
{
	const PlayerVehicles& playerVehicles = connection.getPlayerVehicles();

	PlayerVehicle vehicle = playerVehicles.getVehicle(carList.getIndex());
	
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

void CarListMenu::sellClick()
{

}

void CarListMenu::selectClick()
{

}

