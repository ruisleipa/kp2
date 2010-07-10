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

void MainMenu::NetGameButton::onClick()
{
	//getParent()->getParent()->goToView("connectmenu");
}

MainMenu::NetGameButton::NetGameButton()
{
	setText("Verkkopeli");
}

void MainMenu::LocalGameButton::onClick()
{
	getParent()->setVisible(false);
	((Container*)getParent()->getParent())->getWidget("localgamemenu")->setVisible(true);
}

MainMenu::LocalGameButton::LocalGameButton()
{
	setText("Yksinpeli");
}

void MainMenu::AboutButton::onClick()
{
	
}

MainMenu::AboutButton::AboutButton()
{
	setText("Tietoja pelistä");
}

void MainMenu::SettingsButton::onClick()
{
	getParent()->setVisible(false);
	((Container*)getParent()->getParent())->getWidget("settingsmenu")->setVisible(true);
}

MainMenu::SettingsButton::SettingsButton()
{
	setText("Asetukset");
}

void MainMenu::QuitButton::onClick()
{
	throw ExitException();
}

MainMenu::QuitButton::QuitButton()
{
	setText("Lopeta");
}





