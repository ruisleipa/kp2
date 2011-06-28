#ifndef GUI_CARLISTMENU_HPP
#define GUI_CARLISTMENU_HPP

#include "gui/menu.hpp"
#include "gui/widgetloader.hpp"
#include "playervehiclebutton.hpp"

class Connection;

class CarListMenu : public Menu
{
	public:
		CarListMenu(Connection& connection, Container& parent);

		virtual void onConnectionEvent(Connection& connection);
		
	private:
		void carlistChange();
		void sellClick();
		void selectClick();
		void vehicleClick(int id);
	
		Connection& connection;
		Container& parent;
		
		PlayerVehicleButton buttons[8];
};

#endif
