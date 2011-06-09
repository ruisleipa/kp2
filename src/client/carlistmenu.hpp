#ifndef GUI_CARLISTMENU_HPP
#define GUI_CARLISTMENU_HPP

#include "gui/menu.hpp"
#include "gui/widgetloader.hpp"

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
		
		WidgetLoader loader;
};

#endif
