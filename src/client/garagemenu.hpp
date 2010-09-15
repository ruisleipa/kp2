#ifndef GARAGEMENU_HPP
#define GARAGEMENU_HPP

#include "container.hpp"
#include "label.hpp"
#include "button.hpp"
#include "image.hpp"
#include "field.hpp"

#include "carshopmenu.hpp"
#include "carlistmenu.hpp"

#include "connection.hpp"

class GarageMenu : public Menu
{
	public:
		GarageMenu(Connection& connection);

		virtual void onResize(Graphics& graphics);
		virtual void onHide();
		
	private:
		void carshopClick();
		void carlistClick();
	
		Connection& m_connection;
		
		CarshopMenu m_carshopmenu;
		CarlistMenu m_carlistmenu;
	
		Texture m_background_texture;
		Image m_background;		
		
		Button m_carshop_button;		
		Button m_carlist_button;
		
};

#endif // GARAGEMENU_HPP
