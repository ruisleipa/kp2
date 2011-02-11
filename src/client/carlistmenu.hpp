#ifndef CARLISTMENU_HPP
#define CARLISTMENU_HPP

#include "playervehiclewidget.hpp"

#include "gui/menu.hpp"
#include "gui/label.hpp"
#include "gui/button.hpp"
#include "gui/listbox.hpp"
#include "gui/rowlayoutcontainer.hpp"
#include "gui/columnlayoutcontainer.hpp"

class Connection;

class CarListMenu : public Menu
{
	public:
		CarListMenu(Connection& connection);

		virtual void onConnectionEvent(Connection& connection);
		
	private:
		void carlistChange();
		void sellClick();
		void selectClick();
	
		Connection& connection;
		
		ColumnLayoutContainer mainContainer;
		
		Listbox carList;
		
		RowLayoutContainer infoContainer;
		
		PlayerVehicleWidget vehicleInfo;

		Button sellButton;		
		Button selectButton;				
};

#endif // CARLISTMENU_HPP
