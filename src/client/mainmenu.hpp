#ifndef MAINMENU_HPP
#define MAINMENU_HPP

#include "gui/container.hpp"
#include "gui/button.hpp"
#include "gui/image.hpp"

#include "graphics/texture.hpp"

class MainMenu : public Container
{
	public:
		MainMenu();
		
		virtual void onResize(Window& window);

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
