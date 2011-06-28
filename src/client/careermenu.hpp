#ifndef CAREERMENU_HPP
#define CAREERMENU_HPP

#include "gui/menu.hpp"
#include "gui/container.hpp"

#include "graphics/texturecollection.hpp"

#include "connection.hpp"

class CareerMenu : public Menu
{
	public:
		CareerMenu(TextureCollection& sidebartextures,Container& gameMenus,Connection& connection);

	private:
		void onConnectionEvent(Connection& connection);
		
		Connection& connection;
		
		Container& gameMenus;
};

#endif // CAREERMENU_HPP
