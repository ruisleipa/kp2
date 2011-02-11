#ifndef INSTALLPARTSMENU_HPP
#define INSTALLPARTSMENU_HPP

#include "gui/menu.hpp"
#include "gui/label.hpp"
#include "gui/button.hpp"
#include "gui/image.hpp"
#include "gui/listbox.hpp"
#include "gui/columnlayoutcontainer.hpp"
#include "gui/rowlayoutcontainer.hpp"

#include "connection.hpp"

class InstallPartsMenu : public Menu
{
	public:
		InstallPartsMenu(Connection& connection);

	private:
		void handleConnectionEvent();
	
		Connection& connection;
	
		ColumnLayoutContainer maincontainer;
		
		RowLayoutContainer carContainer;
		
		RowLayoutContainer carPartContainer;
		
		Label carPartLabel;		
		Listbox carPartList;
		
		RowLayoutContainer partContainer;
		
		Label partLabel;		
		Listbox partList;
};

#endif // INSTALLPARTSMENU_HPP
