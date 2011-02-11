#include "installpartsmenu.hpp"

InstallPartsMenu::InstallPartsMenu(Connection& connection):
	connection(connection)
{
	connection.addEventHandler(std::tr1::bind(&InstallPartsMenu::handleConnectionEvent,this));
	
	addWidget(container);
	
	container.setFactorSize(Vector2D(1,1));
	
	container.addWidget(carContainer);
	container.addWidget(partContainer);
	
	carContainer.setFluid(true);
	carContainer.addWidget(carTitleContainer);
	carContainer.addWidget(carPartList);
	carContainer.showOuterPadding(false);
	
	carTitleContainer.setFactorSize(Vector2D(0,0.25));
	carTitleContainer.showOuterPadding(false);
	carTitleContainer.addWidget(carName);
	carTitleContainer.addWidget(carImage);
	
	carName.setFluid(true);	
	
	carImage.setFluid(true);	
	
	carPartList.setFluid(true);
	
	partContainer.setFluid(true);
	partContainer.addWidget(partList);
	partContainer.addWidget(installButton);
	partContainer.addWidget(sellButton);
	partContainer.showOuterPadding(false);
	
	partList.setFluid(true);
	
	installButton.setText("Asenna");
	installButton.autoSize();
	
	sellButton.setText("Myy Osa");
	sellButton.autoSize();
}

void InstallPartsMenu::handleConnectionEvent()
{
	partList.clearItems();
	
	const PlayerParts& parts = connection.getPlayerParts();
		
	for(size_t i = 0; i < parts.getPartCount(); ++i)
	{
		PlayerPart part = parts.getPart(i);
	
		partList.addItem(part.name, i);
	}
}
