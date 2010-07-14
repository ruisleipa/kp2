#ifndef UI_HPP
#define UI_HPP

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

#include "careermenu.hpp"

#include "garagemenu.hpp"

#include "tuningmenu.hpp"

#include "graphics.hpp"

class Ui
{
	public:
		void draw();
	
		Ui(Events& events,Graphics& graphics,Connection& connection);

	private:			
		Events& m_events;
		Graphics& m_graphics;
		Connection& m_connection;
		
		FontLoader m_font_loader;
		
		Window m_root_window;
		
		MainMenu m_mainmenu;
		SettingsMenu m_settingsmenu;
		ConnectMenu m_connectmenu;
		LocalGameMenu m_localgamemenu;
		NewLocalGameMenu m_newlocalgamemenu;
				
		CareerMenu m_careermenu;
		
		GarageMenu m_garagemenu;
			
		TuningMenu m_tuningmenu;

};

const float PADDING=0.02;
const float ITEM_HEIGHT=0.05;

const Vector2D BACK_BUTTON_POSITION(PADDING,1.0-ITEM_HEIGHT-PADDING);
const Vector2D NEXT_BUTTON_POSITION(0.5,1.0-ITEM_HEIGHT-PADDING);
const Vector2D BUTTON_HEIGHT(0.0,ITEM_HEIGHT+0.005);

const Vector2D TITLE_POSITION(PADDING,PADDING);
const Vector2D TITLE_SIZE(0.96,0.1);
const Vector2D CONTENT_POSITION(PADDING,PADDING*2+TITLE_SIZE.getY());
const Vector2D FIELD_SIZE(0.5-PADDING,ITEM_HEIGHT);

const float CAREER_SIDEBAR_WIDTH=0.20;

const Vector2D CAREER_MENU_POSITION(CAREER_SIDEBAR_WIDTH-0.005,0);
const Vector2D CAREER_MENU_SIZE(1.0-CAREER_SIDEBAR_WIDTH+0.01,1);

const float CAREER_SUBMENU_TOP_MARGIN=PADDING*2.0+ITEM_HEIGHT;

const Vector2D CAREER_SUBMENU_POSITION=Vector2D(CAREER_SIDEBAR_WIDTH+PADDING,CAREER_SUBMENU_TOP_MARGIN)-CAREER_MENU_POSITION;
const Vector2D CAREER_SUBMENU_SIZE(1.0-CAREER_SIDEBAR_WIDTH-PADDING*2,1-PADDING-CAREER_SUBMENU_TOP_MARGIN);

const Vector2D CAREER_SIDEBAR_POSITION(0,0);
const Vector2D CAREER_SIDEBAR_SIZE(CAREER_SIDEBAR_WIDTH,1);

const Vector2D TAB_SPACING(0.02,0);

#endif // UI_HPP
