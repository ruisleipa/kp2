#ifndef TABBEDMENUCONTAINER_HPP
#define TABBEDMENUCONTAINER_HPP

#include "menucontainer.hpp"

class TabbedMenuContainer: public MenuContainer
{
	public:
		void addMenu(std::string name,Menu& menu,std::string label);
		
		TabbedMenuContainer(TextureCollection& backgroundtextures);
		
	private:
		ColumnLayoutContainer buttonContainer;
	
};

#endif // CONTAINER_HPP

