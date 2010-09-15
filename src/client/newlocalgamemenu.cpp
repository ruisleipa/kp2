#include "newlocalgamemenu.hpp"

#include <iostream>

#include "ui.hpp"
#include "utils/string.hpp"
#include "net/packet.hpp"

NewLocalGameMenu::NewLocalGameMenu(Connection& connection):
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
	getParent()->showOnlyWidget("localgamemenu");
}

void NewLocalGameMenu::startClickHandler()
{
	if(connection.startLocalServer())
	{
		Packet packet;
		packet.setType(PLAYER_NAME);
		packet<<nameField.getText();
		
		connection.writeToServer(packet);
		
		Packet packet2;
		packet2.setType(PLAYER_MONEY);
		
		connection.writeToServer(packet2);
		
		packet2.setType(CARSHOP_LIST);		
		connection.writeToServer(packet2);
		
		packet2.setType(PARTSHOP_LIST);		
		connection.writeToServer(packet2);
	
		getParent()->showOnlyWidget("careermenu");
	}
}

