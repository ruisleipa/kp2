#include "machiningmenu.hpp"

#include <iostream>
#include <sstream>

#include "ui.hpp"
#include "graphics.hpp"
#include "shared/string.hpp"
#include "connection.hpp"

MachiningMenu::MachiningMenu()
{
	m_background_texture.load("data/images/submenu.png");
	m_background.setTexture(&m_background_texture);
	m_background.setStretched(true);

	m_car_title.setText("Autossa:");	
	m_part_title.setText("Varastossa:");	

	m_install_button.setText("Asenna");
	m_sell_button.setText("Myy Osa");
	
	addWidget(&m_background);
	
	m_title_row.addWidget(&m_car_title);
	m_title_row.addWidget(&m_part_title);
		
	addWidget(&m_title_row);
	
	m_list_row.addWidget(&m_car_part_list);
	m_list_row.addWidget(&m_part_list);
		
	addWidget(&m_list_row);
	
	addWidget(&m_install_button);	
	addWidget(&m_sell_button);	
}

void MachiningMenu::onResize(Graphics& graphics)
{
	setPosition(CAREER_SUBMENU_POSITION);
	setSize(CAREER_SUBMENU_SIZE);
	
	m_background.setSize(CAREER_SUBMENU_SIZE);
	
	m_title_row.setPosition(Vector2D(0,0));
	
	Vector2D title_row_size;
	title_row_size.setX(CAREER_SUBMENU_SIZE.getX());
	title_row_size.setY(PADDING+ITEM_HEIGHT+PADDING);	
	m_title_row.setSize(title_row_size);	
	
	m_list_row.setPosition(m_title_row.getSize()*Vector2D(0,1));	
	m_list_row.setSize(CAREER_SUBMENU_SIZE*Vector2D(1,0.5));
	
	m_install_button.autoSize();
	m_install_button.setPosition(CAREER_SUBMENU_SIZE*Vector2D(0.5,1)-m_install_button.getSize()*Vector2D(0,1)-Vector2D(0,PADDING));

	m_sell_button.autoSize();
	m_sell_button.setPosition(CAREER_SUBMENU_SIZE*Vector2D(0.5,1)-m_install_button.getSize()*Vector2D(0,1)-Vector2D(0,PADDING*2)-m_sell_button.getSize()*Vector2D(0,1));	
}

void MachiningMenu::onShow()
{

}

