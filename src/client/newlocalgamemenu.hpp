#ifndef NEWLOCALGAMEMENU_HPP
#define NEWLOCALGAMEMENU_HPP

#include "gui/menu.hpp"
#include "gui/label.hpp"
#include "gui/select.hpp"
#include "gui/button.hpp"
#include "gui/image.hpp"
#include "gui/field.hpp"

#include "connection.hpp"

class NewLocalGameMenu : public Menu
{
	public:
		NewLocalGameMenu(Connection& connection);

		virtual void onResize(Window& window);
		virtual void onShow();
		
	private:
		void backClickHandler();
		void startClickHandler();
	
		Connection& connection;

		Label title;

		Label nameLabel;
		Label difficultyLabel; 
		
		Field nameField;
		Select difficultySelect;
		
		Button backButton;		
		Button startButton;
};

#endif // NEWLOCALGAMEMENU_HPP
