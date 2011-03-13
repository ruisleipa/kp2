#include "settingsmenu.hpp"

#include <iostream>

#include "ui.hpp"
#include "utils/string.hpp"

#include "sounds/musicplayer.hpp"
#include "graphics/window.hpp"

SettingsMenu::SettingsMenu(Window& window, MusicPlayer& musicPlayer):
	window(window),
	musicPlayer(musicPlayer),
	windowOptionsChanged(false)
{
	setVisible(false);

	title.setFont(Font("title"));
	title.setText("Asetukset");			
	
	sizeLabel.setText("Ikkunan koko");
	fullscreenLabel.setText("Kokoruututila");
	vsyncLabel.setText("Vsync");	
	musicVolumeLabel.setText("Musiikin voimakkuus");	
	
	std::vector<Vector2D> possibleSizes = window.getPossibleSizes();
	std::vector<Vector2D>::iterator i;
	
	for(i=possibleSizes.begin();i!=possibleSizes.end();++i)
	{
		std::string str;
		str+=convertToString((*i).getX());
		str+="x";
		str+=convertToString((*i).getY());
		
		sizeSelect.addItem(str);
	}
	
	fullscreenSelect.addItem("ei");
	fullscreenSelect.addItem("kyllä");
	
	vsyncSelect.addItem("ei");
	vsyncSelect.addItem("kyllä");
	
	musicVolumeSelect.addItem("0 %");
	musicVolumeSelect.addItem("10 %");
	musicVolumeSelect.addItem("20 %");
	musicVolumeSelect.addItem("30 %");
	musicVolumeSelect.addItem("40 %");
	musicVolumeSelect.addItem("50 %");
	musicVolumeSelect.addItem("60 %");
	musicVolumeSelect.addItem("70 %");
	musicVolumeSelect.addItem("80 %");
	musicVolumeSelect.addItem("90 %");
	musicVolumeSelect.addItem("100 %");
	
	backButton.setText("Takaisin");
	backButton.setClickHandler(std::tr1::bind(&SettingsMenu::backClick,this));
	applyButton.setText("Ota käyttöön");
	applyButton.setClickHandler(std::tr1::bind(&SettingsMenu::applyClick,this));

	addWidget(background);
	
	addWidget(title);
	
	addWidget(sizeLabel);
	addWidget(fullscreenLabel);
	addWidget(vsyncLabel);	
	addWidget(musicVolumeLabel);	
			
	addWidget(sizeSelect);
	addWidget(fullscreenSelect);	
	addWidget(vsyncSelect);
	addWidget(musicVolumeSelect);
		
	addWidget(backButton);	
	addWidget(applyButton);
}

void SettingsMenu::onResize(Window& window)
{
	setSize(Vector2D(1,1));
	background.setSize(Vector2D(1,1));
		
	title.setPosition(TITLE_POSITION);
	title.setSize(TITLE_SIZE);
		
	Vector2D buttonpos=CONTENT_POSITION;

	sizeLabel.setPosition(buttonpos);
	sizeLabel.autoSize();
	buttonpos+=BUTTON_HEIGHT;
	
	fullscreenLabel.setPosition(buttonpos);
	fullscreenLabel.autoSize();
	buttonpos+=BUTTON_HEIGHT;
	
	vsyncLabel.setPosition(buttonpos);
	vsyncLabel.autoSize();
	buttonpos+=BUTTON_HEIGHT;
	
	musicVolumeLabel.setPosition(buttonpos);
	musicVolumeLabel.autoSize();
	buttonpos+=BUTTON_HEIGHT;
	
	buttonpos=CONTENT_POSITION;
	buttonpos.setX(0.5);
	
	sizeSelect.setPosition(buttonpos);
	sizeSelect.autoSize();	
	sizeSelect.setChangeHandler(std::tr1::bind(&SettingsMenu::handleDisplayOptionChange, this));
	buttonpos+=BUTTON_HEIGHT;
	
	fullscreenSelect.setPosition(buttonpos);
	fullscreenSelect.autoSize();
	fullscreenSelect.setChangeHandler(std::tr1::bind(&SettingsMenu::handleDisplayOptionChange,this));
	buttonpos+=BUTTON_HEIGHT;	

	vsyncSelect.setPosition(buttonpos);
	vsyncSelect.autoSize();
	vsyncSelect.setChangeHandler(std::tr1::bind(&SettingsMenu::handleDisplayOptionChange, this));
	buttonpos+=BUTTON_HEIGHT;	
	
	musicVolumeSelect.setPosition(buttonpos);
	musicVolumeSelect.autoSize();
	buttonpos+=BUTTON_HEIGHT;

	backButton.setPosition(BACK_BUTTON_POSITION);
	backButton.autoSize();

	applyButton.setPosition(NEXT_BUTTON_POSITION);
	applyButton.autoSize();

}

void SettingsMenu::handleEvent(Event* event)
{
	Menu::handleEvent(event);
	
	if(dynamic_cast<ShowEvent*>(event))
	{
		updateDisplayOptions();
		updateMusicOptions();
	}
}

void SettingsMenu::handleDisplayOptionChange()
{
	windowOptionsChanged = true;
}

void SettingsMenu::updateDisplayOptions()
{
	std::vector<Vector2D> possibleSizes = window.getPossibleSizes();
	
	for(size_t i=0;i<possibleSizes.size();++i)
	{
		if(window.getSize() == possibleSizes[i])
		{
			sizeSelect.setIndex(i);
			break;
		}			
	}		

	fullscreenSelect.setIndex(window.isFullscreen());
	
	vsyncSelect.setIndex(window.getVsyncPreference());
	
	sizeSelect.autoSize();	
	fullscreenSelect.autoSize();
	vsyncSelect.autoSize();
	
	windowOptionsChanged = false;
}

void SettingsMenu::updateMusicOptions()
{
	int index = musicPlayer.getVolume() / 10;
	
	musicVolumeSelect.setIndex(index);
}

void SettingsMenu::backClick()
{
	getParent()->showOnlyWidget("mainmenu");
}

void SettingsMenu::applyClick()
{
	if(windowOptionsChanged)
	{
		std::vector<Vector2D> possibleSizes = window.getPossibleSizes();
		Vector2D size=possibleSizes[sizeSelect.getIndex()];

		bool fullscreen=fullscreenSelect.getIndex();
		bool vsync=vsyncSelect.getIndex();
		
		window.setVideoMode(size,32,fullscreen);
		window.setVsyncPreference(vsync);
		
		updateDisplayOptions();
	}
	
	int musicVolume = musicVolumeSelect.getIndex()*10;
	
	std::cout << musicVolume << std::endl;
	
	musicPlayer.setVolume(musicVolume);	
	
	updateMusicOptions();
}

