#include "tuningmenu.hpp"

#include <iostream>

#include "ui.hpp"
#include "graphics.hpp"
#include "shared/string.hpp"
#include "connection.hpp"

TuningMenu::TuningMenu()
{
	m_install_button.setText("Asenna osia");
	m_machining_button.setText("Työstöt");
	m_buy_button.setText("Osakauppa");
	m_adjust_button.setText("Säädöt");
	m_dyno_button.setText("Penkitys");
	
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

void TuningMenu::InstallButton::onClick()
{
	TuningMenu* menu=dynamic_cast<TuningMenu*>(getParent());
	
	menu->m_installpartsmenu.setVisible(true);
	menu->m_partshopmenu.setVisible(false);
}

void TuningMenu::BuyButton::onClick()
{
	TuningMenu* menu=dynamic_cast<TuningMenu*>(getParent());
	
	menu->m_installpartsmenu.setVisible(false);
	menu->m_partshopmenu.setVisible(true);
}

void TuningMenu::DynoButton::onClick()
{
	TuningMenu* menu=dynamic_cast<TuningMenu*>(getParent());
	
	menu->m_installpartsmenu.setVisible(false);
	menu->m_partshopmenu.setVisible(false);
}

void TuningMenu::AdjustButton::onClick()
{
	TuningMenu* menu=dynamic_cast<TuningMenu*>(getParent());
	
	menu->m_installpartsmenu.setVisible(false);
	menu->m_partshopmenu.setVisible(false);
}

void TuningMenu::MachiningButton::onClick()
{
	TuningMenu* menu=dynamic_cast<TuningMenu*>(getParent());
	
	menu->m_installpartsmenu.setVisible(false);
	menu->m_partshopmenu.setVisible(false);
}
