#ifndef GUI_MAINMENU_HPP
#define GUI_MAINMENU_HPP

#include "gui/menucontainer.hpp"
#include "gui/menu.hpp"
#include "gui/widgetloader.hpp"

#include "graphics/texturecollection.hpp"

class MainMenu : public Menu
{
	public:
		MainMenu(MenuContainer& menuContainer, TextureCollection& textureCollection);

	private:
		MenuContainer& menuContainer;

		WidgetLoader loader;
	
		void remotegameClickHandler();
		void localgameClickHandler();
		void aboutClickHandler();		
		void settingsClickHandler();
		void quitClickHandler();
};

#endif
