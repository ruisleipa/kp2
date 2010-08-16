#include "mainmenu.hpp"

#include <iostream>

#include "ui.hpp"

MainMenu::MainMenu()
{
	setSize(Vector2D(1,1));

	m_background_texture=Texture("data/images/mainmenu.png");
	m_background.setTexture(&m_background_texture);
	m_background.setFill(true);
	
	m_title_texture=Texture("data/images/kp2_txt.png");
	m_title.setTexture(&m_title_texture);
	
	m_net_game_button.setText("Verkkopeli");	
	
	m_local_game_button.setText("Yksinpeli");
	m_local_game_button.setClickHandler(Callback0(this,&MainMenu::localgameClickHandler));
	
	m_about_button.setText("Tietoja pelistä");
	
	m_settings_button.setText("Asetukset");
	m_settings_button.setClickHandler(Callback0(this,&MainMenu::settingsClickHandler));
	
	m_quit_button.setText("Lopeta");
	m_quit_button.setClickHandler(Callback0(this,&MainMenu::quitClickHandler));
	
	addChild(m_background);
	
	addChild(m_title);
	
	//addChild(&m_net_game_button);
	addChild(m_local_game_button);
	addChild(m_about_button);
	addChild(m_settings_button);
	addChild(m_quit_button);
}

void MainMenu::onResize(Window& window)
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
	getParent()->getChild("localgamemenu")->setVisible(true);
}

void MainMenu::aboutClickHandler()
{

}

void MainMenu::settingsClickHandler()
{
	setVisible(false);
	getParent()->getChild("settingsmenu")->setVisible(true);
}

void MainMenu::quitClickHandler()
{
	//throw ExitException();
}


