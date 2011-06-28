#ifndef INSTALLPARTSMENU_HPP
#define INSTALLPARTSMENU_HPP

#include "gui/menu.hpp"
#include "gui/widgetloader.hpp"

#include "playerpartbutton.hpp"

class Connection;

class InstallPartsMenu : public Menu
{
	public:
		InstallPartsMenu(Connection& connection, Container& parent);

	private:
		void handleConnectionEvent();
		
		void handleInstallClick(int id);
		void handleUninstallClick(int id);
	
		void fillVehicleInfo();
		void fillParts();
		void fillVehicleParts();
	
		Connection& connection;
		Container& parent;
		
		std::list<std::tr1::shared_ptr<PlayerPartButton> > buttons;
		std::list<std::tr1::shared_ptr<PlayerPartButton> > vehicleButtons;
};

#endif // INSTALLPARTSMENU_HPP
