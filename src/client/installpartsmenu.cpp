#include "installpartsmenu.hpp"

#include "connection.hpp"

InstallPartsMenu::InstallPartsMenu(Connection& connection):
	connection(connection)
{
	connection.addEventHandler(std::tr1::bind(&InstallPartsMenu::handleConnectionEvent,this));
	
	addWidget(mainContainer);
	
	mainContainer.setFactorSize(Vector2D(1,1));	
	mainContainer.addWidget(vehicleInfo);
	mainContainer.addWidget(rightContainer);

	vehicleInfo.setFluid(true);	
	
	rightContainer.setFluid(true);
	rightContainer.showOuterPadding(false);
	rightContainer.addWidget(partsContainer);	
	rightContainer.addWidget(graph);
	
	partsContainer.setFluid(true);
	partsContainer.showOuterPadding(false);
	partsContainer.addWidget(vehicleContainer);	
	partsContainer.addWidget(partContainer);
	
	vehicleContainer.setFluid(true);	
	vehicleContainer.showOuterPadding(false);
	vehicleContainer.addWidget(vehiclePartLabel);
	vehicleContainer.addWidget(vehiclePartList);
	vehicleContainer.addWidget(uninstallButton);
	
	vehiclePartLabel.setText("Osat autossa:");
	vehiclePartLabel.autoSize();
	
	vehiclePartList.setFluid(true);
	
	uninstallButton.setText("Irrota osa");
	uninstallButton.autoSize();
	uninstallButton.setClickHandler(std::tr1::bind(&InstallPartsMenu::handleUninstallButtonClick,this));	
	
	partContainer.setFluid(true);		
	partContainer.showOuterPadding(false);
	partContainer.addWidget(partLabel);
	partContainer.addWidget(partList);
	partContainer.addWidget(installButton);
	
	partLabel.setText("Osat tallissa:");
	partLabel.autoSize();
	
	partList.setFluid(true);
	
	installButton.setText("Asenna osa");
	installButton.autoSize();
	installButton.setClickHandler(std::tr1::bind(&InstallPartsMenu::handleInstallButtonClick,this));

	graph.setFluid(true);
}

void InstallPartsMenu::handleInstallButtonClick()
{
	if(connection.getActiveVehicleId() == 0)
		return;
		
	connection.installPart(partList.getCurrentItemTag());
}

void InstallPartsMenu::handleUninstallButtonClick()
{
	if(connection.getActiveVehicleId() == 0)
		return;
		
	connection.uninstallPart(vehiclePartList.getCurrentItemTag());
}

void InstallPartsMenu::handleConnectionEvent()
{
	fillVehicleInfo();
	fillParts();
	fillVehicleParts();
	fillPerformanceGraph();
}

void InstallPartsMenu::fillVehicleInfo()
{
	if(connection.getActiveVehicleId() == 0)
		return;
		
	vehicleInfo.showVehicle(connection, connection.getActiveVehicleId());
}

void InstallPartsMenu::fillParts()
{
	if(connection.getActiveVehicleId() == 0)
		return;
		
	partList.clearItems();
	
	std::vector<Protocol::PartId> ids = connection.getPlayerParts().getKeys();	
		
	for(size_t i = 0; i < ids.size(); ++i)
	{
		Protocol::Part part = connection.getPlayerParts().getItem(ids[i]);
		
		partList.addItem(part.name, ids[i]);
	}
}

void InstallPartsMenu::fillVehicleParts()
{
	if(connection.getActiveVehicleId() == 0)
		return;

	vehiclePartList.clearItems();
		
	const Protocol::Vehicle& vehicle = connection.getPlayerVehicles().getItem(connection.getActiveVehicleId());
	
	std::vector<Protocol::PartId> vehiclePartIds = vehicle.parts.getKeys();	
		
	for(size_t i = 0; i < vehiclePartIds.size(); ++i)
	{
		Protocol::Part part = vehicle.parts.getItem(vehiclePartIds[i]);
		
		vehiclePartList.addItem(part.name, vehiclePartIds[i]);
	}	
}

void InstallPartsMenu::fillPerformanceGraph()
{
	const Protocol::PerformanceData data = connection.getPerformanceData();
		
	graph.setPrimaryData(data.power, Color(1, 0, 0), "Teho\n(kW)", data.power.getMax() * 1.25);
	graph.setSecondaryData(data.torque, Color(0, 0, 1), "Vääntö\n(Nm)", data.torque.getMax() * 2.5);
	graph.setDomain(0, 10000);	
}
