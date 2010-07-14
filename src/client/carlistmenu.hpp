#ifndef CARLISTMENU_HPP
#define CARLISTMENU_HPP

#include "container.hpp"
#include "label.hpp"
#include "button.hpp"
#include "image.hpp"
#include "field.hpp"
#include "listbox.hpp"

#include "connection.hpp"

class CarlistMenu : public Container
{
	public:
		CarlistMenu();

		virtual void onResize(Graphics& graphics);
		virtual void onConnectionEvent(Connection& connection);
		
	private:
		Texture m_background_texture;
		Image m_background;
		
		Texture m_car_texture;
		Image m_car_image;
		
		Label m_car_name;
		Label m_car_info;
		
		class CarListbox: public Listbox
		{
			public:				
				void onChange();			
		}m_car_list;
		
		std::vector<Vehicle> m_vehicles;
		
		class SellButton: public Button
		{
			public:				
				void onClick();
		}m_sell_button;
		
		class SelectButton: public Button
		{
			public:				
				void onClick();
		}m_select_button;				
};

#endif // CARLISTMENU_HPP
