#ifndef GUI_NEWLOCALGAMEMENU_HPP
#define GUI_NEWLOCALGAMEMENU_HPP

#include "gui/menucontainer.hpp"
#include "gui/menu.hpp"
#include "gui/widgetloader.hpp"

#include "connection.hpp"

class NewLocalGameMenu : public Menu
{
	public:
		NewLocalGameMenu(MenuContainer& menuContainer, Connection& connection);

		virtual void onShow();
		
	private:
		void backClickHandler();
		void startClickHandler();
	
		MenuContainer& menuContainer;
		Connection& connection;

		WidgetLoader loader;
};

#endif
