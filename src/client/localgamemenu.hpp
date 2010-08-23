#ifndef LOCALGAMEMENU_HPP
#define LOCALGAMEMENU_HPP

#include "gui/container.hpp"
#include "gui/label.hpp"
#include "gui/button.hpp"
#include "gui/image.hpp"

class LocalGameMenu : public Container
{
	public:
		LocalGameMenu();

		virtual void onResize(Window& window);
		virtual void onShow();
		
	private:
		void backClickHandler();
		void newClickHandler();

		Label title;
		
		Button newGameButton;
		Button loadGameButton;				
		Button backButton;
};

#endif // LOCALGAMEMENU_HPP
