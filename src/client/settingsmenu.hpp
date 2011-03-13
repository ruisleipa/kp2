#ifndef SETTINGSMENU_HPP
#define SETTINGSMENU_HPP

#include "gui/menu.hpp"
#include "gui/label.hpp"
#include "gui/select.hpp"
#include "gui/button.hpp"
#include "gui/image.hpp"

class Window;
class SettingsMenu : public Menu
{
	public:
		SettingsMenu(Window& window);

		virtual void onResize(Window& window);
		virtual void handleEvent(Event* event);
	
	private:
		void handleDisplayOptionChange();
	
		void updateDisplayOptions();
		void backClick();
		void applyClick();
		
		Window& window;
		
		bool windowOptionsChanged;

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
