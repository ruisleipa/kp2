#ifndef SETTINGSMENU_HPP
#define SETTINGSMENU_HPP

#include "gui/menucontainer.hpp"
#include "gui/menu.hpp"
#include "gui/label.hpp"
#include "gui/select.hpp"
#include "gui/button.hpp"
#include "gui/image.hpp"

class Window;
class MusicPlayer;

class SettingsMenu : public Menu
{
	public:
		SettingsMenu(MenuContainer& menuContainer, Window& window, MusicPlayer& musicPlayer);

		virtual void onResize(Window& window);
		virtual void handleEvent(Event* event);
	
	private:
		void handleDisplayOptionChange();
	
		void updateDisplayOptions();
		void updateMusicOptions();

		void backClick();
		void applyClick();
		
		MenuContainer& menuContainer;
		Window& window;
		MusicPlayer& musicPlayer;
		
		bool windowOptionsChanged;

		Image background;
		
		Label title;

		Label sizeLabel;
		Select sizeSelect;
		Label fullscreenLabel; 
		Select fullscreenSelect;
		Label vsyncLabel; 
		Select vsyncSelect;
		Label musicVolumeLabel; 
		Select musicVolumeSelect;
		
		Button backButton;
		Button applyButton;
};

#endif // SETTINGSMENU_HPP
