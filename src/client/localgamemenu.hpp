#ifndef LOCALGAMEMENU_HPP
#define LOCALGAMEMENU_HPP

#include "gui/menucontainer.hpp"
#include "gui/menu.hpp"
#include "gui/label.hpp"
#include "gui/button.hpp"
#include "gui/image.hpp"

class LocalGameMenu : public Menu
{
	public:
		LocalGameMenu(MenuContainer& menuContainer);

		virtual void onResize(Window& window);
		virtual void onShow();
		
	private:
		MenuContainer& menuContainer;
	
		void backClickHandler();
		void newClickHandler();

		Label title;
		
		Button newGameButton;
		Button loadGameButton;				
		Button backButton;
};

#endif // LOCALGAMEMENU_HPP
