#include "localgamemenu.hpp"

#include <iostream>

#include "ui.hpp"

LocalGameMenu::LocalGameMenu(MenuContainer& menuContainer):
	menuContainer(menuContainer)
{
	title.setFont(Font("title"));
	title.setText("Yksinpeli");			
	
	newGameButton.setText("Uusi tilanne");
	newGameButton.setClickHandler(std::tr1::bind(&LocalGameMenu::newClickHandler,this));
	loadGameButton.setText("Lataa tilanne");
	
	backButton.setText("Peruuta");
	backButton.setClickHandler(std::tr1::bind(&LocalGameMenu::backClickHandler,this));
	
	addWidget(title);
	
	addWidget(newGameButton);
	addWidget(loadGameButton);	
	
	addWidget(backButton);	
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
	menuContainer.showOnlyWidget("mainmenu");
}

void LocalGameMenu::newClickHandler()
{
	menuContainer.showOnlyWidget("newlocalgamemenu");
}

