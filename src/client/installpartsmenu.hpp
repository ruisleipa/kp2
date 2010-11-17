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

		virtual void handleEvent(Event* event);
		
	private:
		Connection& connection;
	
		ColumnLayoutContainer container;
		
		RowLayoutContainer carContainer;
		
		ColumnLayoutContainer carTitleContainer;
		
		Label carName;		
		Image carImage;
		
		Listbox carParts;
		
		RowLayoutContainer partContainer;
		
		Listbox parts;		
		
		Button installButton;
		Button sellButton;
};

#endif // INSTALLPARTSMENU_HPP
