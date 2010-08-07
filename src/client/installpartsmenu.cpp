#include "installpartsmenu.hpp"

#include <iostream>
#include <sstream>

#include "ui.hpp"
#include "graphics.hpp"
#include "shared/string.hpp"
#include "connection.hpp"

InstallpartsMenu::InstallpartsMenu()
{
	m_background_texture.load("data/images/submenu.png");
	m_background.setTexture(&m_background_texture);
	m_background.setStretched(true);

	m_car_title.setText("Autossa:");	
	m_part_title.setText("Varastossa:");
	m_car_part_list.setText("1.0 L s4\njoku kansi\njokunokka\njoku kaasari\njokuimusarja\njokupakosarja\nyms.");
	
	m_part_list.addItem("1.0 L s4");
	m_part_list.addItem("1.1 L s4");
	m_part_list.addItem("1.4 L s4");
	m_part_list.addItem("1.6 L s4");
	m_part_list.addItem("Kaasari");
	m_part_list.addItem("SUPADUPAKIT");
	
	m_install_button.setText("Asenna");
	m_sell_button.setText("Myy Osa");
	
	addWidget(&m_background);
	addWidget(&m_car_title);
	addWidget(&m_part_title);
	addWidget(&m_car_part_list);
	addWidget(&m_part_list);	
	
	addWidget(&m_install_button);	
	addWidget(&m_sell_button);	
}

void InstallpartsMenu::onResize(Graphics& graphics)
{
	setPosition(CAREER_SUBMENU_POSITION);
	setSize(CAREER_SUBMENU_SIZE);
	
	m_background.setSize(CAREER_SUBMENU_SIZE);
	
	m_car_title.setPosition(Vector2D(PADDING,PADDING));
	m_car_title.autoSize();
	
	m_part_title.setPosition(CAREER_SUBMENU_SIZE*Vector2D(0.5,0)+Vector2D(0,PADDING));
	m_part_title.autoSize();
	
	m_part_list.setPosition(CAREER_SUBMENU_SIZE*Vector2D(0.5,0)+Vector2D(0,ITEM_HEIGHT+PADDING));
	m_part_list.setSize(CAREER_SUBMENU_SIZE*Vector2D(0.5,0.6));
	
	m_car_part_list.setPosition(Vector2D(PADDING,PADDING)+Vector2D(0,ITEM_HEIGHT));
	m_car_part_list.setSize(CAREER_SUBMENU_SIZE*Vector2D(0.5,0.6));
	
	m_install_button.autoSize();
	m_install_button.setPosition(CAREER_SUBMENU_SIZE*Vector2D(0.5,1)-m_install_button.getSize()*Vector2D(0,1)-Vector2D(0,PADDING));

	m_sell_button.autoSize();
	m_sell_button.setPosition(CAREER_SUBMENU_SIZE*Vector2D(0.5,1)-m_install_button.getSize()*Vector2D(0,1)-Vector2D(0,PADDING*2)-m_sell_button.getSize()*Vector2D(0,1));	
}

void InstallpartsMenu::onShow()
{

}

