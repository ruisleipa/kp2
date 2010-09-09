#ifndef CAREERMENU_HPP
#define CAREERMENU_HPP

#include "gui/container.hpp"
#include "gui/label.hpp"
#include "gui/button.hpp"
#include "gui/image.hpp"
#include "gui/field.hpp"

#include "graphics/texturecollection.hpp"

class CareerMenu : public Container
{
	public:
		CareerMenu(TextureCollection& sidebartextures,Container& topLevelGameMenus);

		virtual void onResize(Window& window);
		virtual void onConnectionEvent(Connection& connection);

	private:
		void garageButtonClick();
		void tuningButtonClick();
		void financeButtonClick();
		void raceButtonClick();
	
		Container& topLevelGameMenus;
		
		Image sidebar;
		
		Label infoLabel;
			
		Button garageButton;
		Button tuningButton;
		Button financeButton;
		Button raceButton;
		
};

#endif // CAREERMENU_HPP
