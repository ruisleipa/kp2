#include "newlocalgamemenu.hpp"

#include <iostream>

#include "ui.hpp"
#include "utils/string.hpp"
#include "net/packet.hpp"

NewLocalGameMenu::NewLocalGameMenu(MenuContainer& menuContainer, Connection& connection):
	menuContainer(menuContainer),
	connection(connection)
{
	title.setFont(Font("title"));
	title.setText("Uusi tilanne");			
	
	nameLabel.setText("Nimi:");
	difficultyLabel.setText("Vaikeusaste:");
	
	difficultySelect.addItem("helppo");
	difficultySelect.addItem("normaali");
	difficultySelect.addItem("vaikea");

	backButton.setText("Peruuta");
	backButton.setClickHandler(std::tr1::bind(&NewLocalGameMenu::backClickHandler,this));
	startButton.setText("Aloita");
	startButton.setClickHandler(std::tr1::bind(&NewLocalGameMenu::startClickHandler,this));
	
	addWidget(title);
	
	addWidget(nameLabel);
	addWidget(difficultyLabel);
		
	addWidget(nameField);	
	addWidget(difficultySelect);
	
	addWidget(backButton);	
	addWidget(startButton);
}

void NewLocalGameMenu::onResize(Window& window)
{
	title.setPosition(TITLE_POSITION);
	title.setSize(TITLE_SIZE);
		
	Vector2D buttonpos=CONTENT_POSITION;

	nameLabel.setPosition(buttonpos);
	nameLabel.autoSize();
	buttonpos+=BUTTON_HEIGHT;
	
	difficultyLabel.setPosition(buttonpos);
	difficultyLabel.autoSize();
	buttonpos+=BUTTON_HEIGHT;
	
	buttonpos=CONTENT_POSITION;
	buttonpos.setX(0.5);
	
	nameField.setPosition(buttonpos);
	nameField.setSize(FIELD_SIZE);	
	buttonpos+=BUTTON_HEIGHT;
	
	difficultySelect.setPosition(buttonpos);
	difficultySelect.autoSize();
	buttonpos+=BUTTON_HEIGHT;	

	backButton.setPosition(BACK_BUTTON_POSITION);
	backButton.autoSize();

	startButton.setPosition(NEXT_BUTTON_POSITION);
	startButton.autoSize();

}

void NewLocalGameMenu::onShow()
{
	nameField.setText("");
	difficultySelect.setIndex(1);
}

void NewLocalGameMenu::backClickHandler()
{
	menuContainer.showOnlyWidget("localgamemenu");
}

void NewLocalGameMenu::startClickHandler()
{
	if(connection.startLocalServer())
	{
		menuContainer.showOnlyWidget("careermenu");
		
		connection.setName(nameField.getText());
	}
}

