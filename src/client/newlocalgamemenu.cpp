#include "newlocalgamemenu.hpp"

#include <iostream>

#include "ui.hpp"
#include "graphics.hpp"
#include "shared/string.hpp"

NewLocalGameMenu::NewLocalGameMenu()
{
	m_background_texture.load("data/images/newlocalgamemenu.png");
	m_background.setTexture(&m_background_texture);
	
	m_title.setFont(Font("title"));
	m_title.setText("Uusi peli");			
	
	m_name_label.setText("Nimi:");
	m_difficulty_label.setText("Vaikeusaste:");
	
	m_difficulty_select.addItem("helppo");
	m_difficulty_select.addItem("normaali");
	m_difficulty_select.addItem("vaikea");

	m_back_button.setText("Peruuta");
	m_start_button.setText("Aloita");

	addWidget(&m_background);
	
	addWidget(&m_title);
	
	addWidget(&m_name_label);
	addWidget(&m_difficulty_label);
		
	addWidget(&m_name_field);	
	addWidget(&m_difficulty_select);
	
	addWidget(&m_back_button);	
	addWidget(&m_start_button);
}

void NewLocalGameMenu::resize(Graphics& graphics)
{
	m_background.setSize(Vector2D(1,1));
		
	m_title.setPosition(TITLE_POSITION);
	m_title.setSize(TITLE_SIZE);
		
	Vector2D buttonpos=CONTENT_POSITION;

	m_name_label.setPosition(buttonpos);
	m_name_label.autoSize();
	buttonpos+=BUTTON_HEIGHT;
	
	m_difficulty_label.setPosition(buttonpos);
	m_difficulty_label.autoSize();
	buttonpos+=BUTTON_HEIGHT;
	
	buttonpos=CONTENT_POSITION;
	buttonpos.setX(0.5);
	
	m_name_field.setPosition(buttonpos);
	m_name_field.setSize(FIELD_SIZE);	
	buttonpos+=BUTTON_HEIGHT;
	
	m_difficulty_select.setPosition(buttonpos);
	m_difficulty_select.autoSize();
	buttonpos+=BUTTON_HEIGHT;	

	m_back_button.setPosition(BACK_BUTTON_POSITION);
	m_back_button.autoSize();

	m_start_button.setPosition(NEXT_BUTTON_POSITION);
	m_start_button.autoSize();

}

void NewLocalGameMenu::onShow()
{
	m_name_field.setText("");
	m_difficulty_select.setIndex(1);
}

void NewLocalGameMenu::BackButton::onClick()
{
	getParent()->setVisible(false);
	((Container*)getParent()->getParent())->getWidget("localgamemenu")->setVisible(true);
}

void NewLocalGameMenu::StartButton::onClick()
{

}

