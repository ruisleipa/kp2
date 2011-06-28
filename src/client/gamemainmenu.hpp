#ifndef CLIENT_GAMEMAINMENU_HPP
#define CLIENT_GAMEMAINMENU_HPP

#include "connection.hpp"
#include "gui/container.hpp"
#include "gui/menu.hpp"

class GameMainMenu : public Menu
{
	public:
		GameMainMenu(Connection& connection, Container& parent);

	private:
		void onConnectionEvent(Connection& connection);
		
		Connection& connection;
		
};

#endif
