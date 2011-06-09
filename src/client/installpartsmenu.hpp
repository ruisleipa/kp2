#ifndef INSTALLPARTSMENU_HPP
#define INSTALLPARTSMENU_HPP

#include "playervehiclewidget.hpp"

#include "gui/menu.hpp"
#include "gui/widgetloader.hpp"

class Connection;

class InstallPartsMenu : public Menu
{
	public:
		InstallPartsMenu(Connection& connection);

	private:
		void handleInstallButtonClick();
		void handleUninstallButtonClick();
		void handleConnectionEvent();
	
		void fillVehicleInfo();
		void fillParts();
		void fillVehicleParts();
		void fillPerformanceGraph();
	
		Connection& connection;
	
		WidgetLoader loader;
};

#endif // INSTALLPARTSMENU_HPP
