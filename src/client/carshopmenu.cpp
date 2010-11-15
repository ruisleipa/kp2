#include "carshopmenu.hpp"

#include <iostream>
#include <sstream>

#include "ui.hpp"
#include "utils/string.hpp"
#include "connection.hpp"

CarShopMenu::CarShopMenu(Connection& connection):
	connection(connection),
	backgroundTexture("data/images/submenu.png")
{
	connection.addEventHandler(std::tr1::bind(&CarShopMenu::onConnectionEvent,this,std::tr1::placeholders::_1));
	
	background.setTexture(backgroundTexture);
	background.setStretched(true);

	carList.setFont(Font("small"));
	carList.setChangeHandler(std::tr1::bind(&CarShopMenu::carlistChange,this));
	
	
	carInfo.setFont(Font("small"));	
	
	buyButton.setText("Osta auto");
	buyButton.autoSize();
	buyButton.setClickHandler(std::tr1::bind(&CarShopMenu::buyClick,this));
				
	addWidget(background);
	
	addWidget(mainContainer);
	
	background.setSize(Vector2D(1,1));	
	mainContainer.setSize(Vector2D(1,1));
	
	mainContainer.addWidget(carList);
	mainContainer.addWidget(infoContainer);
	
	carList.setFluid(true);	
	infoContainer.setFluid(true);	
	
	infoContainer.addWidget(titleContainer);
	infoContainer.addWidget(carInfo);
	infoContainer.addWidget(buyButton);
	infoContainer.showOuterPadding(false);
	
	titleContainer.setPixelSize(Vector2D(0,60));
	carInfo.setFluid(true);	
		
	titleContainer.addWidget(carName);
	titleContainer.addWidget(carImage);
	titleContainer.showOuterPadding(false);
	
	carName.setFluid(true);	
	carImage.setFluid(true);	
	
}

void CarShopMenu::onResize(Window& window)
{
	
	
}

void CarShopMenu::onConnectionEvent(Connection& connection)
{
	carList.clearItems();
	
	for(int i=0;i<=connection.getCarshopVehicleMaxId();++i)
	{
		Vehicle vehicle;
	
		if(connection.getCarshopVehicle(i,vehicle))
		{
			carList.addItem(vehicle.getName(),i);
		}
	}	
}

void CarShopMenu::carlistChange()
{
	Vehicle vehicle;
	
	if(!connection.getCarshopVehicle(carList.getCurrentItemTag(),vehicle))
	{
		return;
	}
	
	carName.setText(vehicle.getName());
		
	std::string image="gamedata/vehicles/";
	image+=vehicle.getImageName();
	carImage.setTexture(Texture(image));
	
	carInfo.setText(vehicle.getGeneralInfoString());
}

void CarShopMenu::buyClick()
{
	connection.buyCar(carList.getIndex());
}

