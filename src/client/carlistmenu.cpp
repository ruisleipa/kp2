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

	background.setTexture(Texture("data/images/submenu.png"));
	background.setStretched(true);

	carList.setFont(Font("small"));
	carList.setChangeHandler(std::tr1::bind(&CarListMenu::carlistChange,this));
	
	carInfo.setFont(Font("small"));

	sellButton.setText("Myy auto");
	sellButton.setClickHandler(std::tr1::bind(&CarListMenu::sellClick,this));
	selectButton.setText("Valitse käyttöautoksi");
	selectButton.setClickHandler(std::tr1::bind(&CarListMenu::selectClick,this));
	
	addWidget(background);
	
	addWidget(mainContainer);
	
	mainContainer.addWidget(carList);
	mainContainer.addWidget(infoContainer);
	
	infoContainer.addWidget(titleContainer);
	infoContainer.addWidget(carInfo);

	infoContainer.showOuterPadding(false);
	
	titleContainer.addWidget(carName);
	titleContainer.addWidget(carImage);
	titleContainer.showOuterPadding(false);
	
}

void CarListMenu::onResize(Window& window)
{
	background.setSize(Vector2D(1,1));
	mainContainer.setSize(Vector2D(1,1));
}

void CarListMenu::onConnectionEvent(Connection& connection)
{std::cout<<"connection event"<<std::endl;
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
	carImage.setSize(carImage.getTexture().getSize()/400);
	carImage.setPosition(Vector2D(1,0)-carImage.getSize()*Vector2D(1,0)+Vector2D(-PADDING,PADDING));
	
	carInfo.setText(vehicle.getGeneralInfoString());
}

void CarListMenu::sellClick()
{

}

void CarListMenu::selectClick()
{

}

