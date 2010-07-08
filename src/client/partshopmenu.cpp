#include "partshopmenu.hpp"

#include <iostream>
#include <sstream>

#include "ui.hpp"
#include "graphics.hpp"
#include "shared/string.hpp"
#include "connection.hpp"

PartshopMenu::PartshopMenu()
{
	m_background_texture.load("data/images/carlistmenu.png");
	m_background.setTexture(&m_background_texture);
	m_background.setStretched(true);

	m_part_texture.load("data/images/parts/engine.jpg");
	m_part_image.setTexture(&m_part_texture);
	
	m_category_info.setText("Tähän tulee kategoriainfo.");	
		
	m_category_list.addItem("Moottorit");
	m_category_list.addItem("Kannet");
	m_category_list.addItem("Nokat");	
	m_category_list.addItem("Kaasarit");
	
	m_part_list.addItem("1.0 L s4");
	m_part_list.addItem("1.1 L s4");
	m_part_list.addItem("1.4 L s4");	
	m_part_list.addItem("1.6 L s4");

	m_buy_button.setText("Osta");
	
	addWidget(&m_background);
	addWidget(&m_category_info);
	addWidget(&m_category_list);
	addWidget(&m_part_image);
	addWidget(&m_part_price);
	addWidget(&m_part_list);	
	
	addWidget(&m_buy_button);	
}

void PartshopMenu::onResize(Graphics& graphics)
{
	setPosition(CAREER_SUBMENU_POSITION);
	setSize(CAREER_SUBMENU_SIZE);
	
	m_background.setSize(CAREER_SUBMENU_SIZE);
	
	m_category_info.setPosition(Vector2D(PADDING,PADDING));
	m_category_info.setSize(CAREER_SUBMENU_SIZE/2-Vector2D(PADDING*1.5,PADDING*1.5));

	m_part_image.setPosition(CAREER_SUBMENU_SIZE*Vector2D(0.5,0)+Vector2D(0,PADDING));
	m_part_image.setSize(CAREER_SUBMENU_SIZE*Vector2D(0.5,0.5)-Vector2D(PADDING,PADDING));
	
	m_category_list.setPosition(CAREER_SUBMENU_SIZE*Vector2D(0,0.5)+Vector2D(PADDING,0));
	m_category_list.setSize(CAREER_SUBMENU_SIZE/2-Vector2D(PADDING*1.5,PADDING*1.5));
	
	m_part_list.setPosition(CAREER_SUBMENU_SIZE*Vector2D(0.5,0.5)+Vector2D(PADDING,PADDING)/2.0);
	m_part_list.setSize(CAREER_SUBMENU_SIZE/2-Vector2D(PADDING*1.5,PADDING*1.5));
	
	m_buy_button.autoSize();
	m_buy_button.setPosition(CAREER_SUBMENU_SIZE*Vector2D(0.5,1)-m_buy_button.getSize()*Vector2D(0,1)-Vector2D(0,PADDING));	
}

void PartshopMenu::onShow()
{

}

void PartshopMenu::BuyButton::onClick()
{

}

