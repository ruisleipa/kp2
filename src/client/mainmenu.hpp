#ifndef MAINMENU_HPP
#define MAINMENU_HPP

#include "window.hpp"
#include "button.hpp"
#include "image.hpp"

class MainMenu : public Window
{
	public:
		MainMenu();
		
		virtual void onResize(Graphics& graphics);

	private:

		Texture m_background_texture;
		Image m_background;
		
		Texture m_title_texture;
		Image m_title;
	
		Button m_net_game_button;	
		Button m_local_game_button;		
		Button m_about_button;
		Button m_settings_button;		
		Button m_quit_button;		
	
		void netgameClickHandler();
		void localgameClickHandler();
		void aboutClickHandler();		
		void settingsClickHandler();
		void quitClickHandler();
};

#endif // MAINMENU_HPP
