#include "playervehiclewidget.hpp"

#include <sstream>

#include "ui.hpp"
#include "graphics/texture.hpp"
#include "connection.hpp"

PlayerVehicleWidget::PlayerVehicleWidget()
{
	addWidget((Widget&)titleContainer, "100%", "25%");
	addWidget(carInfo, "100%", "75%");
	showOuterPadding(false);
	
	titleContainer.showOuterPadding(false);
	titleContainer.addWidget(carName, "2~", "100%");
	titleContainer.addWidget(carImage, "1~", "100%");
	
	carInfo.setFont(Font("small"));	
}

void PlayerVehicleWidget::showVehicle(Connection& connection, size_t vehicleId)
{
	const Protocol::Vehicle& vehicle = connection.getPlayerVehicles().getItem(vehicleId);
	
	carName.setText(vehicle.name);
		
	std::string image = "gamedata/vehicleimages/";
	image += vehicle.imageName;
	carImage.setTexture(Texture(image));
	
	std::stringstream ss;
	
	ss << "Vuosimalli: " << vehicle.year << std::endl;
	ss << "Korin paino: " << vehicle.chassisWeight << " kg" << std::endl;
	ss << "Kokonaispaino: " << vehicle.totalWeight << " kg" << std::endl;
	
	carInfo.setText(ss.str());
}
