#ifndef CLIENT_REMOTEGAMEMENU_HPP
#define CLIENT_REMOTEGAMEMENU_HPP

#include "gui/menu.hpp"
#include "gui/widgetloader.hpp"
#include "gui/menucontainer.hpp"

#include "connection.hpp"

class RemoteGameMenu : public Menu
{
	public:
		RemoteGameMenu(MenuContainer& menuContainer, Connection& connection);

		virtual void onShow();
		
	private:
		void backClickHandler();
		void connectClickHandler();
	
		MenuContainer& menuContainer;
		Connection& connection;
		
		WidgetLoader loader;
};

#endif
