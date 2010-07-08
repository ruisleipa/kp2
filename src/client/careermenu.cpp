#include "careermenu.hpp"

#include <iostream>

#include "ui.hpp"
#include "sdl.hpp"
#include "graphics.hpp"
#include "shared/string.hpp"
#include "connection.hpp"

CareerMenu::CareerMenu():
	m_bg_time(SDL_GetTicks())
{
	m_background_files.push_back(Texture("data/images/backgrounds/block.png"));
	m_background_files.push_back(Texture("data/images/backgrounds/brakedisk.png"));
	m_background_files.push_back(Texture("data/images/backgrounds/charger.png"));
	m_background_files.push_back(Texture("data/images/backgrounds/cooler.png"));
	m_background_files.push_back(Texture("data/images/backgrounds/cylinderhead.png"));
	m_background_files.push_back(Texture("data/images/backgrounds/diff.png"));
	m_background_files.push_back(Texture("data/images/backgrounds/engine.png"));
	m_background_files.push_back(Texture("data/images/backgrounds/engine1.png"));
	m_background_files.push_back(Texture("data/images/backgrounds/engine2.png"));
	m_background_files.push_back(Texture("data/images/backgrounds/exhaust.png"));
	m_background_files.push_back(Texture("data/images/backgrounds/intake.png"));
	m_background_files.push_back(Texture("data/images/backgrounds/tire.png"));
	m_background_files.push_back(Texture("data/images/backgrounds/tools.png"));

	m_sidebar_texture.load("data/images/careermenu.png");
	m_sidebar.setTexture(&m_sidebar_texture);
	m_sidebar.setFill(true);
	//m_sidebar.setColor(Color(0.3,0.6,0.8));
	
	m_background.setFill(true);
	m_background_back.setFill(true);
	
	m_garage_button.setText("Autot");
	m_tuning_button.setText("Viritys");
	m_finance_button.setText("Raha-asiat");
	m_race_button.setText("Kisat");
	
	addWidget(&m_background);
	addWidget(&m_background_back);
	addWidget(&m_sidebar);
		
	addWidget(&m_info_label);
	
	addWidget(&m_garage_button);
	addWidget(&m_tuning_button);
	addWidget(&m_finance_button);
	addWidget(&m_race_button);
	
	changeBackground();
}

void CareerMenu::onDraw(Graphics& graphics)
{
	float alpha=(SDL_GetTicks()-m_bg_time)/100.0;
	if(alpha > 1.0)
		alpha = 1.0;
	
	m_background_back.setColor(Color(1,1,1,1.0-alpha));
}

void CareerMenu::onResize(Graphics& graphics)
{
	setSize(Vector2D(1,1));
	
	m_background.setSize(CAREER_MENU_SIZE);
	m_background.setPosition(CAREER_MENU_POSITION);
	m_background_back.setSize(CAREER_MENU_SIZE);
	m_background_back.setPosition(CAREER_MENU_POSITION);
	
	m_sidebar.setSize(CAREER_SIDEBAR_SIZE-Vector2D(0.005,0));
	
	m_info_label.setPosition(TITLE_POSITION);
	m_info_label.autoSize();
	
	Vector2D buttonpos=CONTENT_POSITION+Vector2D(0,0.05);

	m_garage_button.setPosition(buttonpos);
	m_garage_button.autoSize();
	buttonpos+=BUTTON_HEIGHT;
	
	m_tuning_button.setPosition(buttonpos);
	m_tuning_button.autoSize();
	buttonpos+=BUTTON_HEIGHT;
	
	m_finance_button.setPosition(buttonpos);
	m_finance_button.autoSize();
	buttonpos+=BUTTON_HEIGHT;
	
	m_race_button.setPosition(buttonpos);
	m_race_button.autoSize();
	buttonpos+=BUTTON_HEIGHT;
}

void CareerMenu::onConnectionEvent(Connection& connection)
{
	std::stringstream ss;
	
	ss<<connection.getName()<<std::endl;
	ss<<connection.getMoney()<<" €";

	m_info_label.setText(ss.str());
	m_info_label.autoSize();
}

void CareerMenu::changeBackground()
{
	int i=rand()%m_background_files.size();
	
	while(m_background.getTexture()==&m_background_files.at(i))
		i=rand()%m_background_files.size();
	
	m_background_back.setTexture(m_background.getTexture());
	m_background.setTexture(&m_background_files.at(i));
	
	m_bg_time=SDL_GetTicks();
}

void CareerMenu::GarageButton::onClick()
{
	getRootWidget("garagemenu")->setVisible(true);
	getRootWidget("tuningmenu")->setVisible(false);
}

void CareerMenu::TuningButton::onClick()
{
	getRootWidget("garagemenu")->setVisible(false);
	getRootWidget("tuningmenu")->setVisible(true);
}

void CareerMenu::FinanceButton::onClick()
{
	getRootWidget("garagemenu")->setVisible(false);
	getRootWidget("tuningmenu")->setVisible(false);
}

void CareerMenu::RaceButton::onClick()
{
	getRootWidget("garagemenu")->setVisible(false);
	getRootWidget("tuningmenu")->setVisible(false);
}

