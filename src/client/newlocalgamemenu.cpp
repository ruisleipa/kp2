#include "newlocalgamemenu.hpp"

#include <iostream>

#include "ui.hpp"
#include "graphics.hpp"
#include "shared/string.hpp"
#include "shared/packet.hpp"

NewLocalGameMenu::NewLocalGameMenu(Connection& connection):
	m_connection(connection)
{
	title.setFont(Font("title"));
	title.setText("Uusi tilanne");			
	
	nameLabel.setText("Nimi:");
	difficultyLabel.setText("Vaikeusaste:");
	
	difficultySelect.addItem("helppo");
	difficultySelect.addItem("normaali");
	difficultySelect.addItem("vaikea");

	backButton.setText("Peruuta");
	backButton.setClickHandler(Callback0(this,&NewLocalGameMenu::backClickHandler));
	startButton.setText("Aloita");
	startButton.setClickHandler(Callback0(this,&NewLocalGameMenu::startClickHandler));
	
	addWidget(&title);
	
	addWidget(&nameLabel);
	addWidget(&difficultyLabel);
		
	addWidget(&nameField);	
	addWidget(&difficultySelect);
	
	addWidget(&backButton);	
	addWidget(&startButton);
}

void NewLocalGameMenu::onResize(Graphics& graphics)
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
	getMenuContainer()->showMenu("localgamemenu");
}

void NewLocalGameMenu::startClickHandler()
{
	if(m_connection.startLocalServer())
	{
		Packet packet;
		packet.setType(PLAYER_NAME);
		packet<<nameField.getText();
		
		m_connection.writeToServer(packet);
		
		Packet packet2;
		packet2.setType(PLAYER_MONEY);
		
		m_connection.writeToServer(packet2);
		
		packet2.setType(CARSHOP_LIST);		
		m_connection.writeToServer(packet2);
		
		packet2.setType(PARTSHOP_LIST);		
		m_connection.writeToServer(packet2);
	
		getMenuContainer()->showMenu("careermenu");
	}
}

