#include "garagemenu.hpp"

#include <iostream>
#include <sstream>

#include "ui.hpp"
#include "graphics.hpp"
#include "shared/string.hpp"
#include "connection.hpp"

CarshopMenu::CarshopMenu(Connection& connection):
	m_connection(connection)
{
	m_background_texture.load("data/images/submenu.png");
	m_background.setTexture(&m_background_texture);
	m_background.setStretched(true);

	m_car_list.setFont(Font("small"));
	m_car_list.setChangeHandler(Callback0(this,&CarshopMenu::carlistChange));
		
	m_car_info.setFont(Font("small"));
	m_car_image.setTexture(&m_car_texture);
	
	m_buy_button.setText("Osta auto");
	m_buy_button.setClickHandler(Callback0(this,&CarshopMenu::buyClick));
				
	addWidget(&m_background);
	addWidget(&m_car_list);
	addWidget(&m_car_image);
	addWidget(&m_car_name);
	addWidget(&m_car_info);
	
	addWidget(&m_buy_button);
	
}

void CarshopMenu::onResize(Graphics& graphics)
{
	setPosition(CAREER_SUBMENU_POSITION);
	setSize(CAREER_SUBMENU_SIZE);
	
	m_background.setSize(CAREER_SUBMENU_SIZE);
	
	m_car_image.setSize(m_car_texture.getSize()/400);
	m_car_image.setPosition(CAREER_SUBMENU_SIZE*Vector2D(1,0)-m_car_image.getSize()*Vector2D(1,0)+Vector2D(-PADDING,PADDING));
	
	m_car_list.setPosition(TITLE_POSITION);
	m_car_list.setSize(CAREER_SUBMENU_SIZE*Vector2D(0.5,1)-Vector2D(PADDING,PADDING)*2);
	
	m_car_name.setPosition(TITLE_POSITION*Vector2D(0,1)+CAREER_SUBMENU_SIZE*Vector2D(0.5,0));
	m_car_name.setSize(CAREER_SUBMENU_SIZE*Vector2D(0.3,0.15));

	m_car_info.setPosition(CAREER_SUBMENU_SIZE*Vector2D(0.5,0.3));
	m_car_info.setSize(CAREER_SUBMENU_SIZE*Vector2D(0.5,0.5)-Vector2D(PADDING,PADDING)*2);
	
	m_buy_button.autoSize();
	m_buy_button.setPosition(CAREER_SUBMENU_SIZE*Vector2D(0.5,1)-m_buy_button.getSize()*Vector2D(0,1)-Vector2D(0,PADDING));
}

void CarshopMenu::onConnectionEvent(Connection& connection)
{
	m_car_list.clearItems();
	
	for(int i=0;i<=connection.getCarshopVehicleMaxId();++i)
	{
		Vehicle vehicle;
	
		if(connection.getCarshopVehicle(i,vehicle))
		{
			m_car_list.addItem(vehicle.getName(),i);
		}
	}	
}

void CarshopMenu::carlistChange()
{
	Vehicle vehicle;
	
	if(!m_connection.getCarshopVehicle(m_car_list.getCurrentItemTag(),vehicle))
	{
		return;
	}
	
	m_car_name.setText(vehicle.getName());
		
	std::string image="gamedata/vehicles/";
	image+=vehicle.getImageName();
	m_car_texture.load(image);
	m_car_image.setSize(m_car_texture.getSize()/400);
	m_car_image.setPosition(CAREER_SUBMENU_SIZE*Vector2D(1,0)-m_car_image.getSize()*Vector2D(1,0)+Vector2D(-PADDING,PADDING));
	
	m_car_info.setText(vehicle.getGeneralInfoString());
}

void CarshopMenu::buyClick()
{
	m_connection.buyCar(m_car_list.getIndex());
}

