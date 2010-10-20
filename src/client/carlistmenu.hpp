#ifndef CARLISTMENU_HPP
#define CARLISTMENU_HPP

#include "gui/menu.hpp"
#include "gui/label.hpp"
#include "gui/button.hpp"
#include "gui/image.hpp"
#include "gui/listbox.hpp"
#include "gui/rowlayoutcontainer.hpp"
#include "gui/columnlayoutcontainer.hpp"

#include "connection.hpp"

class CarListMenu : public Menu
{
	public:
		CarListMenu(Connection& connection);

		virtual void onResize(Window& window);
		virtual void onConnectionEvent(Connection& connection);
		
	private:
		void carlistChange();
		void sellClick();
		void selectClick();
	
		Connection& connection;
		
		ColumnLayoutContainer mainContainer;
		ColumnLayoutContainer titleContainer;
		RowLayoutContainer infoContainer;
	
		Image background;		
		Image carImage;
		
		Label carName;
		Label carInfo;
		
		Listbox carList;
		
		std::vector<Vehicle> vehicles;
		
		Button sellButton;		
		Button selectButton;				
};

#endif // CARLISTMENU_HPP
