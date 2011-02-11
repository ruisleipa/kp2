#ifndef PARTSHOPMENU_HPP
#define PARTSHOPMENU_HPP

#include "gui/menu.hpp"
#include "gui/columnlayoutcontainer.hpp"
#include "gui/rowlayoutcontainer.hpp"
#include "gui/label.hpp"
#include "gui/button.hpp"
#include "gui/image.hpp"
#include "gui/field.hpp"
#include "gui/listbox.hpp"

#include "connection.hpp"

class PartShopMenu : public Menu
{
	public:
		PartShopMenu(Connection& connection);

		virtual void onResize(Window& window);
				
	private:
		void categoryChangeHandler();
		void partChange();
		void buyHandler();
		
		Connection& connection;
	
		ColumnLayoutContainer container;
				
		RowLayoutContainer categoryContainer;
				
		Label categoryInfo;
		Listbox categoryBox;	
			
		RowLayoutContainer partContainer;

		Listbox partBox;	

		RowLayoutContainer partInfoContainer;
		
		Image partImage;
		Label partInfo;
		Button buyButton;
};

#endif // PARTSHOPMENU_HPP
