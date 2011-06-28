#ifndef GUI_CARSHOPMENU_HPP
#define GUI_CARSHOPMENU_HPP

#include "gui/menu.hpp"
#include "gui/widgetloader.hpp"

#include "graphics/texture.hpp"

#include "connection.hpp"

class CarShopMenu : public Menu
{
	public:
		CarShopMenu(Connection& connection, Container& parent);

		void onConnectionEvent(Connection& connection);
		
	private:
		void carlistChange();
		void buyClick();
	
		Connection& connection;
		
		WidgetLoader loader;
};

#endif
