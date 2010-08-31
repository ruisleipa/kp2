#ifndef CAREERMENU_HPP
#define CAREERMENU_HPP

#include "gui/menu.hpp"
#include "gui/label.hpp"
#include "gui/button.hpp"
#include "gui/image.hpp"
#include "gui/field.hpp"

class CareerMenu : public Menu
{
	public:
		CareerMenu(TextureCollection& sidebartextures,MenuContainer& topLevelGameMenus);

		virtual void onResize(Window& window);
		virtual void onConnectionEvent(Connection& connection);

	private:
		void garageButtonClick();
		void tuningButtonClick();
		void financeButtonClick();
		void raceButtonClick();
	
		MenuContainer& topLevelGameMenus;
		
		Image sidebar;
		
		Label infoLabel;
			
		Button garageButton;
		Button tuningButton;
		Button financeButton;
		Button raceButton;
		
};

#endif // CAREERMENU_HPP
