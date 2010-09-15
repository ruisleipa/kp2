#ifndef MAINMENU_HPP
#define MAINMENU_HPP

#include "gui/menu.hpp"
#include "gui/button.hpp"
#include "gui/image.hpp"

#include "graphics/texturecollection.hpp"

class MainMenu : public Menu
{
	public:
		MainMenu(TextureCollection& textureCollection);
		
		virtual void onResize(Window& window);

	private:
		Image background;
		Image title;
	
		Button localgameButton;		
		Button aboutButton;
		Button settingsButton;		
		Button quitButton;		
	
		void localgameClickHandler();
		void aboutClickHandler();		
		void settingsClickHandler();
		void quitClickHandler();
};

#endif // MAINMENU_HPP
