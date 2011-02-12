#include "playervehiclewidget.hpp"

#include <sstream>

#include "ui.hpp"
#include "graphics/texture.hpp"
#include "connection.hpp"

PlayerVehicleWidget::PlayerVehicleWidget(Connection& connection):
	connection(connection)
{
	addWidget(mainContainer);
	
	mainContainer.setFactorSize(Vector2D(1,1));
	
	mainContainer.addWidget(carList);
	mainContainer.addWidget(infoContainer);
	
	carList.setFluid(true);	
	infoContainer.setFluid(true);	
	
	infoContainer.addWidget(titleContainer);
	infoContainer.addWidget(carInfo);
	infoContainer.showOuterPadding(false);
	
	titleContainer.setFactorSize(Vector2D(0,0.25));
	carInfo.setFluid(true);	
		
	titleContainer.addWidget(carName);
	titleContainer.addWidget(carImage);
	titleContainer.showOuterPadding(false);
	
	carName.setFluid(true);	
	carImage.setFluid(true);	
}

void PlayerVehicleWidget::showVehicle(Connection& connection, size_t vehicleId)
{
	Protocol::Vehicle vehicle = connection.getPlayerVehicles().getItem(vehicleId);
	
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
