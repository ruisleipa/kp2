#include "localgamemenu.hpp"

#include <iostream>

#include "ui.hpp"

LocalGameMenu::LocalGameMenu()
{
	setVisible(false);

	title.setFont(Font("title"));
	title.setText("Yksinpeli");			
	
	newGameButton.setText("Uusi tilanne");
	newGameButton.setClickHandler(Callback0(this,&LocalGameMenu::newClickHandler));
	loadGameButton.setText("Lataa tilanne");
	
	//m_save_game_button.setText("Tallenna peli");
	
	backButton.setText("Peruuta");
	backButton.setClickHandler(Callback0(this,&LocalGameMenu::backClickHandler));
	
	addChild(title);
	
	addChild(newGameButton);
	addChild(loadGameButton);	
	
	addChild(backButton);	
}

void LocalGameMenu::onResize(Window& window)
{
	setSize(Vector2D(1,1));
		
	title.setPosition(TITLE_POSITION);
	title.setSize(TITLE_SIZE);
		
	Vector2D buttonpos=CONTENT_POSITION;

	newGameButton.setPosition(buttonpos);
	newGameButton.autoSize();
	buttonpos+=BUTTON_HEIGHT;
	
	loadGameButton.setPosition(buttonpos);
	loadGameButton.autoSize();
	buttonpos+=BUTTON_HEIGHT;
	
	backButton.setPosition(BACK_BUTTON_POSITION);
	backButton.autoSize();
}

void LocalGameMenu::onShow()
{

}

void LocalGameMenu::backClickHandler()
{
	setVisible(false);
	getParent()->getChild("mainmenu")->setVisible(true);
}

void LocalGameMenu::newClickHandler()
{
	setVisible(false);
	getParent()->getChild("newlocalgamemenu")->setVisible(true);
}

