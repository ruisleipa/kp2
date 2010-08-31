#include "careermenu.hpp"

#include <iostream>

#include "ui.hpp"
#include "connection.hpp"

CareerMenu::CareerMenu(TextureCollection& sidebartextures,MenuContainer& topLevelGameMenus):
	topLevelGameMenus(topLevelGameMenus)
{
	sidebar.setTexture(sidebartextures.getTexture("background"));
	sidebar.setFill(true);
	
	garageButton.setText("Autot");
	garageButton.setClickHandler(Callback0(this,&CareerMenu::garageButtonClick));
	tuningButton.setText("Viritys");
	tuningButton.setClickHandler(Callback0(this,&CareerMenu::tuningButtonClick));
	financeButton.setText("Raha-asiat");
	financeButton.setClickHandler(Callback0(this,&CareerMenu::financeButtonClick));
	raceButton.setText("Kisat");
	raceButton.setClickHandler(Callback0(this,&CareerMenu::raceButtonClick));
	
	addWidget(sidebar);
		
	addWidget(infoLabel);
	
	addWidget(garageButton);
	addWidget(tuningButton);
	addWidget(financeButton);
	addWidget(raceButton);
	
	addWidget(topLevelGameMenus);
}

void CareerMenu::onResize(Window& window)
{
	sidebar.setSize(CAREER_SIDEBAR_SIZE);
	
	infoLabel.setPosition(TITLE_POSITION);
	infoLabel.autoSize();
	
	Vector2D buttonpos=CONTENT_POSITION;

	garageButton.setPosition(buttonpos);
	garageButton.autoSize();
	buttonpos+=BUTTON_HEIGHT;
	
	tuningButton.setPosition(buttonpos);
	tuningButton.autoSize();
	buttonpos+=BUTTON_HEIGHT;
	
	financeButton.setPosition(buttonpos);
	financeButton.autoSize();
	buttonpos+=BUTTON_HEIGHT;
	
	raceButton.setPosition(buttonpos);
	raceButton.autoSize();
	buttonpos+=BUTTON_HEIGHT;
	
	topLevelGameMenus.setSize(Vector2D(1.0-CAREER_SIDEBAR_SIZE.getX(),1));
	topLevelGameMenus.setPosition(Vector2D(CAREER_SIDEBAR_SIZE.getX(),0));
}

void CareerMenu::onConnectionEvent(Connection& connection)
{
	std::stringstream ss;
	
	ss<<connection.getName()<<std::endl;
	ss<<connection.getMoney()<<" €";

	infoLabel.setText(ss.str());
	infoLabel.autoSize();
}

void CareerMenu::garageButtonClick()
{
	topLevelGameMenus.showMenu("garage");
}

void CareerMenu::tuningButtonClick()
{
	topLevelGameMenus.showMenu("tuning");
}

void CareerMenu::financeButtonClick()
{
	topLevelGameMenus.showMenu("finance");
}

void CareerMenu::raceButtonClick()
{
	topLevelGameMenus.showMenu("race");
}

