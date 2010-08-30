#ifndef SETTINGSMENU_HPP
#define SETTINGSMENU_HPP

#include "graphics/texturecollection.hpp"

#include "gui/menu.hpp"
#include "gui/label.hpp"
#include "gui/select.hpp"
#include "gui/button.hpp"
#include "gui/image.hpp"

class SettingsMenu : public Menu
{
	public:
		SettingsMenu(Window& window,TextureCollection& textures);

		virtual void onResize(Window& window);
		virtual void onShow();
	
		void updateDisplayOptions();
			
	private:
		void backClick();
		void applyClick();
		
		Window& window;

		Image background;
		
		Label title;

		Label sizeLabel;
		Select sizeSelect;
		Label fullscreenLabel; 
		Select fullscreenSelect;
		Label vsyncLabel; 
		Select vsyncSelect;
		
		Button backButton;
		Button applyButton;
};

#endif // SETTINGSMENU_HPP
