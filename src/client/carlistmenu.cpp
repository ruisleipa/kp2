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

	carList.setFont(Font("small"));
	carList.setChangeHandler(std::tr1::bind(&CarListMenu::carlistChange,this));
	
	carInfo.setFont(Font("small"));

	sellButton.setText("Myy auto");
	sellButton.setClickHandler(std::tr1::bind(&CarListMenu::sellClick,this));
	selectButton.setText("Valitse käyttöautoksi");
	selectButton.setClickHandler(std::tr1::bind(&CarListMenu::selectClick,this));
	
	addWidget(mainContainer);
	
	mainContainer.setSize(Vector2D(1,1));
	
	mainContainer.addWidget(carList);
	mainContainer.addWidget(infoContainer);
	
	carList.setFluid(true);	
	infoContainer.setFluid(true);	
	
	infoContainer.addWidget(titleContainer);
	infoContainer.addWidget(carInfo);
	//infoContainer.addWidget(buyButton);
	infoContainer.showOuterPadding(false);
	
	titleContainer.setPixelSize(Vector2D(0,60));
	carInfo.setFluid(true);	
		
	titleContainer.addWidget(carName);
	titleContainer.addWidget(carImage);
	titleContainer.showOuterPadding(false);
	
	carName.setFluid(true);	
	carImage.setFluid(true);	
	
}

void CarListMenu::onResize(Window& window)
{
	mainContainer.setSize(Vector2D(1,1));
}

void CarListMenu::onConnectionEvent(Connection& connection)
{
	carList.clearItems();
	
	for(int i=0;i<=connection.getPlayerVehicleMaxId();++i)
	{
		Vehicle vehicle;
	
		if(connection.getPlayerVehicle(i,vehicle))
		{
			carList.addItem(vehicle.getName(),i);
		}
	}
}

void CarListMenu::carlistChange()
{
	Vehicle vehicle;
	
	if(!connection.getPlayerVehicle(carList.getCurrentItemTag(),vehicle))
	{
		return;
	}
	
	carName.setText(vehicle.getName());
		
	std::string image="gamedata/vehicles/";
	image+=vehicle.getImageName();
	carImage.setTexture(Texture(image));
	
	carInfo.setText(vehicle.getGeneralInfoString());
}

void CarListMenu::sellClick()
{

}

void CarListMenu::selectClick()
{

}

