#include "mainmenu.hpp"

#include <iostream>

#include "ui.hpp"

MainMenu::MainMenu(TextureCollection& textureCollection)
{
	background.setFill(true);
	
	title.setTexture(textureCollection.getTexture("title"));
	
	localgameButton.setText("Yksinpeli");
	localgameButton.setClickHandler(std::tr1::bind(&MainMenu::localgameClickHandler,this));
	
	aboutButton.setText("Tietoja pelistä");
	
	settingsButton.setText("Asetukset");
	settingsButton.setClickHandler(std::tr1::bind(&MainMenu::settingsClickHandler,this));
	
	quitButton.setText("Lopeta");
	quitButton.setClickHandler(std::tr1::bind(&MainMenu::quitClickHandler,this));
	
	addWidget(background);
	
	addWidget(title);
	
	addWidget(localgameButton);
	addWidget(aboutButton);
	addWidget(settingsButton);
	addWidget(quitButton);
}

void MainMenu::onResize(Window& window)
{
	setSize(Vector2D(1,1));

	background.setSize(Vector2D(1,1));

	title.setPosition(TITLE_POSITION);
	title.setSize(TITLE_SIZE);
	
	Vector2D buttonpos=CONTENT_POSITION;

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

void MainMenu::localgameClickHandler()
{
	getParent()->showOnlyWidget("localgamemenu");
}

void MainMenu::aboutClickHandler()
{

}

void MainMenu::settingsClickHandler()
{
	getParent()->showOnlyWidget("settingsmenu");
}

void MainMenu::quitClickHandler()
{
	//throw ExitException();
}


