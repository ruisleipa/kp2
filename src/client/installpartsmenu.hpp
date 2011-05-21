#ifndef INSTALLPARTSMENU_HPP
#define INSTALLPARTSMENU_HPP

#include "playervehiclewidget.hpp"

#include "gui/menu.hpp"
#include "gui/label.hpp"
#include "gui/button.hpp"
#include "gui/graph.hpp"
#include "gui/image.hpp"
#include "gui/listbox.hpp"
#include "gui/columnlayoutcontainer.hpp"
#include "gui/rowlayoutcontainer.hpp"

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
	
		ColumnLayoutContainer mainContainer;
		
		PlayerVehicleWidget vehicleInfo;
		
		RowLayoutContainer rightContainer;
		
		Graph graph;
		
		ColumnLayoutContainer partsContainer;
		
		RowLayoutContainer vehicleContainer;
		
		Label vehiclePartLabel;		
		Listbox vehiclePartList;
		Button uninstallButton;
		
		RowLayoutContainer partContainer;
		
		Label partLabel;		
		Listbox partList;
		Button installButton;
};

#endif // INSTALLPARTSMENU_HPP
