#include "mainmenu.hpp"

#include <iostream>

#include "ui.hpp"

#include "events.hpp"

MainMenu::MainMenu()
{
	m_background_texture.load("data/images/mainmenu.png");
	m_background.setTexture(&m_background_texture);
	m_background.setFill(true);
	
	m_title_texture.load("data/images/kp2_txt.png");
	m_title.setTexture(&m_title_texture);
	
	m_net_game_button.setText("Verkkopeli");	
	
	m_local_game_button.setText("Yksinpeli");
	m_local_game_button.setClickHandler(Callback0(this,&MainMenu::localgameClickHandler));
	
	m_about_button.setText("Tietoja pelistä");
	
	m_settings_button.setText("Asetukset");
	m_settings_button.setClickHandler(Callback0(this,&MainMenu::settingsClickHandler));
	
	m_quit_button.setText("Lopeta");
	m_quit_button.setClickHandler(Callback0(this,&MainMenu::quitClickHandler));
	
	addWidget(&m_background);
	
	addWidget(&m_title);
	
	//addWidget(&m_net_game_button);
	addWidget(&m_local_game_button);
	addWidget(&m_about_button);
	addWidget(&m_settings_button);
	addWidget(&m_quit_button);
}

void MainMenu::onResize(Graphics& graphics)
{
	m_background.setSize(Vector2D(1,1));

	m_title.setPosition(TITLE_POSITION);
	m_title.setSize(TITLE_SIZE);
	
	Vector2D buttonpos=CONTENT_POSITION;

	//m_net_game_button.setPosition(buttonpos);
	//m_net_game_button.autoSize();
	//buttonpos+=BUTTON_HEIGHT;
	
	m_local_game_button.setPosition(buttonpos);
	m_local_game_button.autoSize();
	buttonpos+=BUTTON_HEIGHT;
	
	m_about_button.setPosition(buttonpos);
	m_about_button.autoSize();
	buttonpos+=BUTTON_HEIGHT;
	
	m_settings_button.setPosition(buttonpos);
	m_settings_button.autoSize();
	buttonpos+=BUTTON_HEIGHT;

	m_quit_button.setPosition(buttonpos);
	m_quit_button.autoSize();
	buttonpos+=BUTTON_HEIGHT;
}

void MainMenu::netgameClickHandler()
{

}

void MainMenu::localgameClickHandler()
{
	setVisible(false);
	getRootWidget("localgamemenu")->setVisible(true);
}

void MainMenu::aboutClickHandler()
{

}

void MainMenu::settingsClickHandler()
{
	setVisible(false);
	getRootWidget("settingsmenu")->setVisible(true);
}

void MainMenu::quitClickHandler()
{
	throw ExitException();
}


