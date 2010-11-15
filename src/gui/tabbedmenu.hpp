#ifndef TABBEDMENU_HPP
#define TABBEDMENU_HPP

#include "menu.hpp"
#include "button.hpp"
#include "container.hpp"
#include "columnlayoutcontainer.hpp"
#include "rowlayoutcontainer.hpp"

#include <tr1/memory>

class TabbedMenu : public Menu
{
	public:
		TabbedMenu();
		
		void addTab(const std::string& label,Widget& widget);
	
	private:
		RowLayoutContainer topContainer;
		ColumnLayoutContainer buttonContainer;
		Container tabContainer;
		
		std::vector<std::tr1::shared_ptr<Button> > buttons;
		
};

#endif // TABBEDMENU_HPP

