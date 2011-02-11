#ifndef CARSHOPMENU_HPP
#define CARSHOPMENU_HPP

#include "gui/menu.hpp"
#include "gui/label.hpp"
#include "gui/button.hpp"
#include "gui/image.hpp"
#include "gui/field.hpp"
#include "gui/listbox.hpp"
#include "gui/rowlayoutcontainer.hpp"
#include "gui/columnlayoutcontainer.hpp"

#include "graphics/texture.hpp"

#include "connection.hpp"

class CarShopMenu : public Menu
{
	public:
		CarShopMenu(Connection& connection);

		virtual void onConnectionEvent(Connection& connection);
		
	private:
		void carlistChange();
		void buyClick();
	
		Connection& connection;
		
		ColumnLayoutContainer mainContainer;
		ColumnLayoutContainer titleContainer;
		RowLayoutContainer infoContainer;
	
		Image carImage;
		
		Label carName;
		Label carInfo;
		
		Listbox carList;		
		Button buyButton;				
};

#endif // CARSHOPMENU_HPP
