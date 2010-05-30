#ifndef __MAINMENU_HPP
#define __MAINMENU_HPP

#include "view.hpp"
#include "button.hpp"
#include "image.hpp"

class MainMenu : public View
{
	public:
		MainMenu();
		
		virtual void calculateLayout();

	private:

		Texture m_background_texture;
		Image m_background;
		
		Texture m_title_texture;
		Image m_title;
	
		class NetGameButton: public Button
		{
			public:		
				NetGameButton();		
				void onClick();
		}m_net_game_button;		
	
		class LocalGameButton: public Button
		{
			public:		
				LocalGameButton();		
				void onClick();
		}m_local_game_button;
		
		class AboutButton: public Button
		{
			public:		
				AboutButton();		
				void onClick();
		}m_about_button;
	
		class SettingsButton: public Button
		{
			public:		
				SettingsButton();		
				void onClick();
		}m_settings_button;		
	
		class QuitButton: public Button
		{
			public:		
				QuitButton();		
				void onClick();
		}m_quit_button;
		
};

#endif // __MAINMENU_HPP
