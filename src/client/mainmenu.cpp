#include "mainmenu.hpp"

#include <iostream>

#include "ui.hpp"

MainMenu::MainMenu(TextureCollection& textureCollection)
{
	background.setFill(true);
	
	title.setTexture(textureCollection.getTexture("title"));
	
	netgameButton.setText("Verkkopeli");	
	
	localgameButton.setText("Yksinpeli");
	localgameButton.setClickHandler(Callback0(this,&MainMenu::localgameClickHandler));
	
	aboutButton.setText("Tietoja pelistä");
	
	settingsButton.setText("Asetukset");
	settingsButton.setClickHandler(Callback0(this,&MainMenu::settingsClickHandler));
	
	quitButton.setText("Lopeta");
	quitButton.setClickHandler(Callback0(this,&MainMenu::quitClickHandler));
	
	addChild(background);
	
	addChild(title);
	
	//addChild(&netgameButton);
	addChild(localgameButton);
	addChild(aboutButton);
	addChild(settingsButton);
	addChild(quitButton);
}

void MainMenu::onResize(Window& window)
{
	setSize(Vector2D(1,1));

	background.setSize(Vector2D(1,1));

	title.setPosition(TITLE_POSITION);
	title.setSize(TITLE_SIZE);
	
	Vector2D buttonpos=CONTENT_POSITION;

	//netgameButton.setPosition(buttonpos);
	//netgameButton.autoSize();
	//buttonpos+=BUTTON_HEIGHT;
	
	localgameButton.setPosition(buttonpos);
	localgameButton.autoSize();
	buttonpos+=BUTTON_HEIGHT;
	
	aboutButton.setPosition(buttonpos);
	aboutButton.autoSize();
	buttonpos+=BUTTON_HEIGHT;
	
	settingsButton.setPosition(buttonpos);
	settingsButton.autoSize();
	buttonpos+=BUTTON_HEIGHT;

	quitButton.setPosition(buttonpos);
	quitButton.autoSize();
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


