#include "garagemenu.hpp"

#include <iostream>

#include "ui.hpp"
#include "graphics.hpp"
#include "shared/string.hpp"
#include "connection.hpp"
#include "careermenu.hpp"

GarageMenu::GarageMenu(Connection& connection):
	m_connection(connection),
	m_carshopmenu(m_connection),
	m_carlistmenu(m_connection)
{
	m_carshop_button.setText("Autokauppa");
	m_carshop_button.setClickHandler(Callback0(this,&GarageMenu::carshopClick));
	m_carlist_button.setText("Autotalli");
	m_carlist_button.setClickHandler(Callback0(this,&GarageMenu::carlistClick));
	
	addWidget(&m_carshop_button);
	addWidget(&m_carlist_button);	
	
	addWidget(&m_carshopmenu);
	addWidget(&m_carlistmenu);
	
	m_carshopmenu.setVisible(false);		
	m_carlistmenu.setVisible(false);	
}

void GarageMenu::onResize(Graphics& graphics)
{
	setPosition(CAREER_MENU_POSITION);
	setSize(CAREER_MENU_SIZE);
	
	Vector2D buttonpos=TITLE_POSITION;

	m_carshop_button.setPosition(buttonpos);
	m_carshop_button.autoSize();
	buttonpos+=m_carshop_button.getSize()*Vector2D(1,0)+TAB_SPACING;
	
	m_carlist_button.setPosition(buttonpos);
	m_carlist_button.autoSize();
	buttonpos+=m_carlist_button.getSize()*Vector2D(1,0)+TAB_SPACING;
}

void GarageMenu::onHide()
{
	m_carshopmenu.setVisible(false);
	m_carlistmenu.setVisible(false);
}

void GarageMenu::carshopClick()
{
	m_carshopmenu.setVisible(true);
	m_carlistmenu.setVisible(false);
	
	CareerMenu* careermenu=dynamic_cast<CareerMenu*>(getRootWidget("careermenu"));
	careermenu->changeBackground();
}

void GarageMenu::carlistClick()
{
	m_carshopmenu.setVisible(false);
	m_carlistmenu.setVisible(true);
	
	CareerMenu* careermenu=dynamic_cast<CareerMenu*>(getRootWidget("careermenu"));
	careermenu->changeBackground();
}


