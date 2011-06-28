#ifndef PARTSHOPMENU_HPP
#define PARTSHOPMENU_HPP

#include "gui/menu.hpp"
#include "gui/widgetloader.hpp"

#include "connection.hpp"

class PartShopMenu : public Menu
{
	public:
		PartShopMenu(Connection& connection, Container& parent);
		
	private:
		void categoryChangeHandler();
		void partChange();
		void buyHandler();
		
		Connection& connection;
	
		WidgetLoader loader;
};

#endif // PARTSHOPMENU_HPP
