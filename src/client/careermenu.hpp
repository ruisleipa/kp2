#ifndef CAREERMENU_HPP
#define CAREERMENU_HPP

#include "gui/menu.hpp"
#include "gui/label.hpp"
#include "gui/button.hpp"
#include "gui/image.hpp"
#include "gui/field.hpp"

#include "graphics/texturecollection.hpp"

#include "connection.hpp"

class CareerMenu : public Menu
{
	public:
		CareerMenu(TextureCollection& sidebartextures,Container& topLevelGameMenus,Connection& connection);

		virtual void onResize(Window& window);
		
	private:
		void onConnectionEvent(Connection& connection);
	
		void garageButtonClick();
		void tuningButtonClick();
		void financeButtonClick();
		void raceButtonClick();
		
		Connection& connection;
		
		Container& topLevelGameMenus;
		
		Image sidebar;
		
		Label infoLabel;
			
		Button garageButton;
		Button tuningButton;
		Button financeButton;
		Button raceButton;
		
};

#endif // CAREERMENU_HPP
