#ifndef CAREERMENU_HPP
#define CAREERMENU_HPP

#include "gui/menu.hpp"
#include "gui/container.hpp"
#include "gui/widgetloader.hpp"

#include "graphics/texturecollection.hpp"

#include "connection.hpp"

class CareerMenu : public Menu
{
	public:
		CareerMenu(TextureCollection& sidebartextures,Container& topLevelGameMenus,Connection& connection);

	private:
		void onConnectionEvent(Connection& connection);
	
		void garageButtonClick();
		void tuningButtonClick();
		void financeButtonClick();
		void raceButtonClick();
		
		Connection& connection;
		
		Container& topLevelGameMenus;
		
		WidgetLoader loader;
};

#endif // CAREERMENU_HPP
