#include "installpartsmenu.hpp"

InstallPartsMenu::InstallPartsMenu(Connection& connection):
	connection(connection)
{
	addWidget(container);
	
	container.setFactorSize(Vector2D(1,1));
	
	container.addWidget(carContainer);
	container.addWidget(partContainer);
	
	carContainer.setFluid(true);
	carContainer.addWidget(carTitleContainer);
	carContainer.addWidget(carParts);
	
	carTitleContainer.setFactorSize(Vector2D(0,0.25));
	carTitleContainer.showOuterPadding(false);
	carTitleContainer.addWidget(carName);
	carTitleContainer.addWidget(carImage);
	
	carName.setFluid(true);	
	
	carImage.setFluid(true);	
	
	carParts.setFluid(true);
	
	partContainer.setFluid(true);
	partContainer.addWidget(parts);
	partContainer.addWidget(installButton);
	partContainer.addWidget(sellButton);
	
	parts.setFluid(true);
	
	installButton.setText("Asenna");
	installButton.autoSize();
	
	sellButton.setText("Myy Osa");
	sellButton.autoSize();
}

void InstallPartsMenu::handleEvent(Event* event)
{
	Menu::handleEvent(event);
	
	if(dynamic_cast<ShowEvent*>(event))
	{
		Vehicle vehicle;
		
		if(!connection.getPlayerVehicle(0,vehicle))
			return;
				
		carName.setText(vehicle.getName());
			
		std::string image="gamedata/vehicles/";
		image+=vehicle.getImageName();
		carImage.setTexture(Texture(image));
	}	
}
