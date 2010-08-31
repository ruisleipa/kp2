#include "careermenu.hpp"

#include <iostream>

#include "ui.hpp"

CareerMenu::CareerMenu(MenuContainer& mainLevelGameMenus,TextureCollection& textureCollection):
	mainLevelGameMenus(mainLevelGameMenus)
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
}

void CareerMenu::onResize(Graphics& graphics)
{
	setSize(Vector2D(1,1));
	
	sidebar.setSize(CAREER_SIDEBAR_SIZE-Vector2D(0.005,0));
	
	infoLabel.setPosition(TITLE_POSITION);
	infoLabel.autoSize();
	
	Vector2D buttonpos=CONTENT_POSITION+Vector2D(0,0.05);

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
	mainLevelGameMenus.showMenu("garage");
}

void CareerMenu::tuningButtonClick()
{
	mainLevelGameMenus.showMenu("tuning");
}

void CareerMenu::financeButtonClick()
{
	mainLevelGameMenus.showMenu("finance");
}

void CareerMenu::raceButtonClick()
{
	mainLevelGameMenus.showMenu("race");
}

