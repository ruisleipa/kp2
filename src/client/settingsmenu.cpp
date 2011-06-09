#include "settingsmenu.hpp"

#include "utils/string.hpp"
#include "sounds/musicplayer.hpp"
#include "graphics/window.hpp"

#include "gui/label.hpp"
#include "gui/select.hpp"
#include "gui/button.hpp"

SettingsMenu::SettingsMenu(MenuContainer& menuContainer, Window& window, MusicPlayer& musicPlayer):
	menuContainer(menuContainer),
	window(window),
	musicPlayer(musicPlayer),
	windowOptionsChanged(false),
	loader("data/ui/settingsmenu.ui")
{
	addWidget(loader.getRootWidget(), "0px", "0px", "100%", "100%");
	
	dynamic_cast<Label&>(getChildByName("title")).setFont(Font("title"));
	
	std::vector<Vector2D> possibleSizes = window.getPossibleSizes();
	std::vector<Vector2D>::iterator i;
	
	Select& sizeSelect = dynamic_cast<Select&>(getChildByName("sizeSelect"));
	
	for(i=possibleSizes.begin();i!=possibleSizes.end();++i)
	{
		std::string str;
		str+=convertToString((*i).getX());
		str+="x";
		str+=convertToString((*i).getY());
		
		sizeSelect.addItem(str);
	}
	
	Select& fullscreenSelect = dynamic_cast<Select&>(getChildByName("fullscreenSelect"));
	
	fullscreenSelect.addItem("ei");
	fullscreenSelect.addItem("kyllä");
	
	fullscreenSelect.setChangeHandler(std::tr1::bind(&SettingsMenu::handleDisplayOptionChange, this));
	
	Select& vsyncSelect = dynamic_cast<Select&>(getChildByName("vsyncSelect"));
	
	vsyncSelect.addItem("ei");
	vsyncSelect.addItem("kyllä");
	
	vsyncSelect.setChangeHandler(std::tr1::bind(&SettingsMenu::handleDisplayOptionChange, this));
	
	Select& musicVolumeSelect = dynamic_cast<Select&>(getChildByName("musicVolumeSelect"));
	
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
	
	musicVolumeSelect.setChangeHandler(std::tr1::bind(&SettingsMenu::handleDisplayOptionChange, this));
	
	dynamic_cast<Button&>(getChildByName("backButton")).setClickHandler(std::tr1::bind(&SettingsMenu::backClick,this));
	dynamic_cast<Button&>(getChildByName("applyButton")).setClickHandler(std::tr1::bind(&SettingsMenu::applyClick,this));
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
			dynamic_cast<Select&>(getChildByName("sizeSelect")).setIndex(i);
			break;
		}			
	}		

	dynamic_cast<Select&>(getChildByName("fullscreenSelect")).setIndex(window.isFullscreen());
	dynamic_cast<Select&>(getChildByName("vsyncSelect")).setIndex(window.getVsyncPreference());
	
	windowOptionsChanged = false;
}

void SettingsMenu::updateMusicOptions()
{
	int index = musicPlayer.getVolume() / 10;
	
	dynamic_cast<Select&>(getChildByName("musicVolumeSelect")).setIndex(index);
}

void SettingsMenu::backClick()
{
	menuContainer.showOnlyWidget("mainmenu");
}

void SettingsMenu::applyClick()
{
	if(windowOptionsChanged)
	{
		std::vector<Vector2D> possibleSizes = window.getPossibleSizes();
		Vector2D size=possibleSizes[dynamic_cast<Select&>(getChildByName("sizeSelect")).getIndex()];

		bool fullscreen=dynamic_cast<Select&>(getChildByName("fullscreenSelect")).getIndex();
		bool vsync=dynamic_cast<Select&>(getChildByName("vsyncSelect")).getIndex();
		
		window.setVideoMode(size,32,fullscreen);
		window.setVsyncPreference(vsync);
		
		updateDisplayOptions();
	}
	
	int musicVolume = dynamic_cast<Select&>(getChildByName("musicVolumeSelect")).getIndex()*10;
	
	musicPlayer.setVolume(musicVolume);	
	
	updateMusicOptions();
}

