#ifndef __LOCALGAMEMENU_HPP
#define __LOCALGAMEMENU_HPP

#include "window.hpp"
#include "label.hpp"
#include "button.hpp"
#include "image.hpp"
#include "field.hpp"

class LocalGameMenu : public Window
{
	public:
		LocalGameMenu();

		virtual void resize(Graphics& graphics);
		virtual void onShow();
		
	private:

		Texture m_background_texture;
		Image m_background;
		
		Label m_title;

		class NewGameButton: public Button
		{
			public:				
				void onClick();
		}m_new_game_button;
		
		Button m_load_game_button;
				
		class BackButton: public Button
		{
			public:				
				void onClick();
		}m_back_button;
};

#endif // __LOCALGAMEMENU_HPP
