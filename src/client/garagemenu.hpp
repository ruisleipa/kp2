#ifndef __GARAGEMENU_HPP
#define __GARAGEMENU_HPP

#include "container.hpp"
#include "label.hpp"
#include "button.hpp"
#include "image.hpp"
#include "field.hpp"

#include "carshopmenu.hpp"
#include "carlistmenu.hpp"

#include "connection.hpp"

class GarageMenu : public Container
{
	public:
		GarageMenu(Connection& connection);

		virtual void onResize(Graphics& graphics);
		virtual void onHide();
		
	private:
		Connection& m_connection;
		
		CarshopMenu m_carshopmenu;
		CarlistMenu m_carlistmenu;
	
		Texture m_background_texture;
		Image m_background;		
		
		class CarshopButton: public Button
		{
			public:				
				void onClick();
		}m_carshop_button;
		
		class CarlistButton: public Button
		{
			public:				
				void onClick();
		}m_carlist_button;
		
};

#endif // __GARAGEMENU_HPP
