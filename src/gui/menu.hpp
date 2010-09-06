#ifndef MENU_HPP
#define MENU_HPP

#include "widgetcontainer.hpp"
#include <map>

#include "menucontainer.hpp"

class Menu : public WidgetContainer
{
	protected:
		MenuContainer* getMenuContainer();
		
	private:
		void setMenuContainer(MenuContainer* menuContainer);
	
		MenuContainer* menuContainer;

		friend class MenuContainer;
};

#endif // MENU_HPP
