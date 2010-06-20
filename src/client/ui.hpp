#ifndef __UI_HPP
#define __UI_HPP

#include <memory>

#include "vector2d.hpp"
#include "fontloader.hpp"
#include "events.hpp"

#include "container.hpp"

#include "mainmenu.hpp"
#include "settingsmenu.hpp"
#include "connectmenu.hpp"
#include "localgamemenu.hpp"
#include "newlocalgamemenu.hpp"

#include "graphics.hpp"

class Ui
{
	public:
		void draw();
	
		Ui(Events& events,Graphics& graphics);

	private:			
		Events& m_events;
		Graphics& m_graphics;
		
		FontLoader m_font_loader;
		
		Window m_root_window;
		
		MainMenu m_mainmenu;
		SettingsMenu m_settingsmenu;
		ConnectMenu m_connectmenu;
		LocalGameMenu m_localgamemenu;
		NewLocalGameMenu m_newlocalgamemenu;
		
};

const float PADDING=0.02;
const float ITEM_HEIGHT=0.06;

const Vector2D BACK_BUTTON_POSITION(PADDING,1.0-ITEM_HEIGHT-PADDING);
const Vector2D NEXT_BUTTON_POSITION(0.5,1.0-ITEM_HEIGHT-PADDING);
const Vector2D BUTTON_HEIGHT(0.0,ITEM_HEIGHT+0.005);

const Vector2D TITLE_POSITION(PADDING,PADDING);
const Vector2D TITLE_SIZE(0.96,0.12);
const Vector2D CONTENT_POSITION(PADDING,0.14);
const Vector2D FIELD_SIZE(0.5-PADDING,ITEM_HEIGHT);

#endif // __UI_HPP
