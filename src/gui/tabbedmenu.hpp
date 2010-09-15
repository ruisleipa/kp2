#ifndef TABBEDMENU_HPP
#define TABBEDMENU_HPP

#include "menu.hpp"

class TabbedMenu : public Menu
{
	public:
		TabbedMenu();
		
		void addTab(const std::string& label,Widget& widget);
	
	private:
		Container buttonContainer;		
		Container tabContainer;
		
};

#endif // TABBEDMENU_HPP

