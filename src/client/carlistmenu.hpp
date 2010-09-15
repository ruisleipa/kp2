#ifndef CARLISTMENU_HPP
#define CARLISTMENU_HPP

#include "container.hpp"
#include "label.hpp"
#include "button.hpp"
#include "image.hpp"
#include "field.hpp"
#include "listbox.hpp"

#include "connection.hpp"

class CarlistMenu : public Menu
{
	public:
		CarlistMenu(Connection& connection);

		virtual void onResize(Graphics& graphics);
		virtual void onConnectionEvent(Connection& connection);
		
	private:
		void carlistChange();
		void sellClick();
		void selectClick();
	
		Connection& m_connection;
	
		Texture m_background_texture;
		Image m_background;
		
		Texture m_car_texture;
		Image m_car_image;
		
		Label m_car_name;
		Label m_car_info;
		
		Listbox m_car_list;
		
		std::vector<Vehicle> m_vehicles;
		
		Button m_sell_button;		
		Button m_select_button;				
};

#endif // CARLISTMENU_HPP
