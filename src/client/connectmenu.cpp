#include "connectmenu.hpp"

#include <iostream>

#include "ui.hpp"
#include "graphics.hpp"
#include "shared/string.hpp"
#include "connection.hpp"

ConnectMenu::ConnectMenu()
{
	m_background_texture.load("data/images/connectmenu.png");
	m_background.setTexture(&m_background_texture);
	
	m_title.setFont(Font("title"));
	m_title.setText("Verkkopeli");			
	
	m_hostname_label.setText("Palvelimen osoite");
	m_port_label.setText("Palvelimen portti");
	
	m_back_button.setText("Peruuta");
	m_connect_button.setText("Yhdistä");

	addWidget(&m_background);
	
	addWidget(&m_title);
	
	addWidget(&m_hostname_label);
	addWidget(&m_port_label);
		
	addWidget(&m_hostname_field);
	addWidget(&m_port_field);	
	
	addWidget(&m_back_button);	
	addWidget(&m_connect_button);
}

void ConnectMenu::calculateLayout()
{
	m_background.setSize(Vector2D(1,1));
		
	m_title.setPosition(TITLE_POSITION);
	m_title.setSize(TITLE_SIZE);
		
	Vector2D buttonpos=CONTENT_POSITION;

	m_hostname_label.setPosition(buttonpos);
	m_hostname_label.autoSize();
	buttonpos+=BUTTON_HEIGHT;
	
	m_port_label.setPosition(buttonpos);
	m_port_label.autoSize();
	buttonpos+=BUTTON_HEIGHT;
	
	buttonpos=CONTENT_POSITION;
	buttonpos.setX(0.5);
	
	m_hostname_field.setPosition(buttonpos);
	m_hostname_field.setSize(FIELD_SIZE);	
	buttonpos+=BUTTON_HEIGHT;
	
	m_port_field.setPosition(buttonpos);
	m_port_field.setSize(FIELD_SIZE);
	buttonpos+=BUTTON_HEIGHT;	

	m_back_button.setPosition(BACK_BUTTON_POSITION);
	m_back_button.autoSize();

	m_connect_button.setPosition(NEXT_BUTTON_POSITION);
	m_connect_button.autoSize();

}

void ConnectMenu::onActivate()
{
	m_hostname_field.setText("");
	m_port_field.setText("");
}

void ConnectMenu::BackButton::onClick()
{
	//Ui::getInstance().goToPreviousView();
}

void ConnectMenu::ConnectButton::onClick()
{
	ConnectMenu* menu=dynamic_cast<ConnectMenu*>(getParent());

	std::string hostname=menu->m_hostname_field.getText();
	
	int port=std::atoi(menu->m_port_field.getText().c_str());
	
//	Connection::getInstance().connect(hostname,port);
}

