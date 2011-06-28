#include "installpartsmenu.hpp"

#include "connection.hpp"

#include "gui/label.hpp"
#include "gui/button.hpp"
#include "gui/rowlayoutcontainer.hpp"

InstallPartsMenu::InstallPartsMenu(Connection& connection, Container& parent):
	Menu("data/ui/installpartsmenu.ui"),
	connection(connection),
	parent(parent)
{
	connection.addEventHandler(std::tr1::bind(&InstallPartsMenu::handleConnectionEvent,this));
	
	getChildByName<Button>("backButton").setClickHandler(std::tr1::bind(&Container::showOnlyWidget, &parent, "gamemainmenu"));
	getChildByName<Button>("performanceButton").setClickHandler(std::tr1::bind(&Container::showOnlyWidget, &parent, "performancemenu"));
	getChildByName<Button>("buyButton").setClickHandler(std::tr1::bind(&Container::showOnlyWidget, &parent, "partshopmenu"));
}

void InstallPartsMenu::handleConnectionEvent()
{
	fillVehicleInfo();
	fillParts();
	fillVehicleParts();
}

void InstallPartsMenu::fillVehicleInfo()
{
	/*if(connection.getActiveVehicleId() == 0)
		return;
	
	PlayerVehicleWidget& vehicleInfo = dynamic_cast<PlayerVehicleWidget&>(getChildByName("vehicleInfo"));
	
	vehicleInfo.showVehicle(connection, connection.getActiveVehicleId());*/
}

void InstallPartsMenu::handleInstallClick(int id)
{
	connection.installPart(id);
}

void InstallPartsMenu::handleUninstallClick(int id)
{
	connection.uninstallPart(id);
}

void InstallPartsMenu::fillParts()
{
	if(connection.getActiveVehicleId() == 0)
		return;
	
	RowLayoutContainer& container = getChildByName<RowLayoutContainer>("parts");
	
	std::list<std::tr1::shared_ptr<PlayerPartButton> >::iterator i;
	
	for(i = buttons.begin(); i != buttons.end(); ++i)
	{
		container.removeWidget(*(i->get()));
	}
	
	buttons.clear();
	
	std::vector<Protocol::PartId> ids = connection.getPlayerParts().getKeys();
	
	for(size_t i = 0; i < ids.size(); ++i)
	{
		Protocol::Part part = connection.getPlayerParts().getItem(ids[i]);
		
		std::tr1::shared_ptr<PlayerPartButton> button(new PlayerPartButton());
		
		button->showPart(part);
		button->setClickHandler(std::tr1::bind(&InstallPartsMenu::handleInstallClick, this, ids[i]));
		
		container.addWidget(*(button.get()), "100%", "auto");
		
		buttons.push_back(button);
	}
}

void InstallPartsMenu::fillVehicleParts()
{
	if(connection.getActiveVehicleId() == 0)
		return;
	
	
	RowLayoutContainer& container = getChildByName<RowLayoutContainer>("vehicleParts");
	
	std::list<std::tr1::shared_ptr<PlayerPartButton> >::iterator i;
	
	for(i = vehicleButtons.begin(); i != vehicleButtons.end(); ++i)
	{
		container.removeWidget(*(i->get()));
	}
	
	vehicleButtons.clear();
	
	const Protocol::Vehicle& vehicle = connection.getPlayerVehicles().getItem(connection.getActiveVehicleId());
	
	std::vector<Protocol::PartId> ids = vehicle.parts.getKeys();
	
	for(size_t i = 0; i < ids.size(); ++i)
	{
		Protocol::Part part = vehicle.parts.getItem(ids[i]);
		
		std::tr1::shared_ptr<PlayerPartButton> button(new PlayerPartButton());
		
		button->showPart(part);
		button->setClickHandler(std::tr1::bind(&InstallPartsMenu::handleUninstallClick, this, ids[i]));
		
		container.addWidget(*(button.get()), "100%", "auto");
		
		vehicleButtons.push_back(button);
	}
}
