#ifndef CARSHOPMENU_HPP
#define CARSHOPMENU_HPP

#include "container.hpp"
#include "label.hpp"
#include "button.hpp"
#include "image.hpp"
#include "field.hpp"
#include "listbox.hpp"

#include "connection.hpp"

class CarshopMenu : public Container
{
	public:
		CarshopMenu(Connection& connection);

		virtual void onResize(Graphics& graphics);
		virtual void onConnectionEvent(Connection& connection);
		
	private:
		void carlistChange();
		void buyClick();
	
		Connection& m_connection;
	
		Texture m_background_texture;
		Image m_background;
		
		Texture m_car_texture;
		Image m_car_image;
		
		Label m_car_name;
		Label m_car_info;
		
		std::vector<Vehicle> m_vehicles;
		
		Listbox m_car_list;		
		Button m_buy_button;				
};

#endif // CARSHOPMENU_HPP
