#include "tuningmenu.hpp"

#include <iostream>

#include "ui.hpp"
#include "graphics.hpp"
#include "shared/string.hpp"
#include "connection.hpp"

TuningMenu::TuningMenu(Connection& connection):
	m_partshopmenu(connection)
{
	m_install_button.setText("Asenna osia");
	m_install_button.setClickHandler(Callback0(this,&TuningMenu::installClick));
	
	m_machining_button.setText("Työstöt");
	m_machining_button.setClickHandler(Callback0(this,&TuningMenu::machiningClick));
	
	m_buy_button.setText("Osakauppa");
	m_buy_button.setClickHandler(Callback0(this,&TuningMenu::buyClick));
	
	m_adjust_button.setText("Säädöt");
	m_adjust_button.setClickHandler(Callback0(this,&TuningMenu::adjustClick));
	
	m_dyno_button.setText("Penkitys");
	m_dyno_button.setClickHandler(Callback0(this,&TuningMenu::dynoClick));
	
	addWidget(&m_install_button);
	addWidget(&m_machining_button);
	addWidget(&m_buy_button);
	addWidget(&m_adjust_button);
	addWidget(&m_dyno_button);
	
	addWidget(&m_partshopmenu);
	addWidget(&m_installpartsmenu);

	m_partshopmenu.setVisible(false);	
	m_installpartsmenu.setVisible(false);	
}

void TuningMenu::onResize(Graphics& graphics)
{
	setPosition(CAREER_MENU_POSITION);
	setSize(CAREER_MENU_SIZE);
	
	Vector2D buttonpos=TITLE_POSITION;

	m_buy_button.setPosition(buttonpos);
	m_buy_button.autoSize();
	buttonpos+=m_buy_button.getSize()*Vector2D(1,0)+TAB_SPACING;	
	
	m_install_button.setPosition(buttonpos);
	m_install_button.autoSize();
	buttonpos+=m_install_button.getSize()*Vector2D(1,0)+TAB_SPACING;
	
	m_machining_button.setPosition(buttonpos);
	m_machining_button.autoSize();
	buttonpos+=m_machining_button.getSize()*Vector2D(1,0)+TAB_SPACING;
	
	m_adjust_button.setPosition(buttonpos);
	m_adjust_button.autoSize();
	buttonpos+=m_adjust_button.getSize()*Vector2D(1,0)+TAB_SPACING;
	
	m_dyno_button.setPosition(buttonpos);
	m_dyno_button.autoSize();
	buttonpos+=m_dyno_button.getSize()*Vector2D(1,0)+TAB_SPACING;
}

void TuningMenu::onHide()
{

}

void TuningMenu::installClick()
{
	m_installpartsmenu.setVisible(true);
	m_partshopmenu.setVisible(false);
}

void TuningMenu::buyClick()
{
	m_installpartsmenu.setVisible(false);
	m_partshopmenu.setVisible(true);
}

void TuningMenu::dynoClick()
{
	m_installpartsmenu.setVisible(false);
	m_partshopmenu.setVisible(false);
}

void TuningMenu::adjustClick()
{
	m_installpartsmenu.setVisible(false);
	m_partshopmenu.setVisible(false);
}

void TuningMenu::machiningClick()
{
	m_installpartsmenu.setVisible(false);
	m_partshopmenu.setVisible(false);
}
