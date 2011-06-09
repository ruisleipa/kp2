#ifndef GUI_LOCALGAMEMENU_HPP
#define GUI_LOCALGAMEMENU_HPP

#include "gui/menucontainer.hpp"
#include "gui/menu.hpp"
#include "gui/widgetloader.hpp"

class LocalGameMenu : public Menu
{
	public:
		LocalGameMenu(MenuContainer& menuContainer);
		
	private:
		MenuContainer& menuContainer;
	
		void backClickHandler();
		void newClickHandler();

		WidgetLoader loader;
};

#endif
