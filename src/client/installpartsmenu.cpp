#include "installpartsmenu.hpp"

#include "connection.hpp"

#include "gui/label.hpp"
#include "gui/button.hpp"
#include "gui/graph.hpp"
#include "gui/image.hpp"
#include "gui/listbox.hpp"
#include "gui/columnlayoutcontainer.hpp"
#include "gui/rowlayoutcontainer.hpp"

InstallPartsMenu::InstallPartsMenu(Connection& connection):
	connection(connection),
	loader("data/ui/installpartsmenu.ui")
{
	addWidget(loader.getRootWidget(), "0px", "0px", "100%", "100%");
	
	connection.addEventHandler(std::tr1::bind(&InstallPartsMenu::handleConnectionEvent,this));
	
	dynamic_cast<Button&>(getChildByName("uninstallButton")).setClickHandler(std::tr1::bind(&InstallPartsMenu::handleUninstallButtonClick,this));	
	dynamic_cast<Button&>(getChildByName("installButton")).setClickHandler(std::tr1::bind(&InstallPartsMenu::handleInstallButtonClick,this));
}

void InstallPartsMenu::handleInstallButtonClick()
{
	if(connection.getActiveVehicleId() == 0)
		return;
		
	Listbox& partList = dynamic_cast<Listbox&>(getChildByName("partList"));
		
	connection.installPart(partList.getCurrentItemTag());
}

void InstallPartsMenu::handleUninstallButtonClick()
{
	if(connection.getActiveVehicleId() == 0)
		return;
	
	Listbox& vehiclePartList = dynamic_cast<Listbox&>(getChildByName("vehiclePartList"));
	
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
	
	PlayerVehicleWidget& vehicleInfo = dynamic_cast<PlayerVehicleWidget&>(getChildByName("vehicleInfo"));
	
	vehicleInfo.showVehicle(connection, connection.getActiveVehicleId());
}

void InstallPartsMenu::fillParts()
{
	if(connection.getActiveVehicleId() == 0)
		return;
	
	Listbox& partList = dynamic_cast<Listbox&>(getChildByName("partList"));
	
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

	Listbox& vehiclePartList = dynamic_cast<Listbox&>(getChildByName("vehiclePartList"));
	
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
	
	Graph& graph = dynamic_cast<Graph&>(getChildByName("graph"));
	
	graph.setPrimaryData(data.power, Color(1, 0, 0), "Teho\n(kW)", data.power.getMax() * 1.25);
	graph.setSecondaryData(data.torque, Color(0, 0, 1), "Vääntö\n(Nm)", data.torque.getMax() * 2.5);
	graph.setDomain(0, 10000);	
}
