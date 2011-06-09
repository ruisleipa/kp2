#ifndef GUI_SETTINGSMENU_HPP
#define GUI_SETTINGSMENU_HPP

#include "gui/menucontainer.hpp"
#include "gui/menu.hpp"
#include "gui/widgetloader.hpp"

class Window;
class MusicPlayer;

class SettingsMenu : public Menu
{
	public:
		SettingsMenu(MenuContainer& menuContainer, Window& window, MusicPlayer& musicPlayer);

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
		
		WidgetLoader loader;
};

#endif
