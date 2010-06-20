#ifndef __APPLICATION_HPP
#define __APPLICATION_HPP

#include <memory>

#include "sdl.hpp"
#include "graphics.hpp"
#include "events.hpp"
#include "connection.hpp"
#include "ui.hpp"

class Application
{
	public:
		void enterMainLoop();		
		
		Application();
		~Application();
		
	private:
		void loadCursor();
		void drawCursor();
	
		Sdl m_sdl;
		Events m_events;
		Graphics m_graphics;
		Connection m_connection;
		FontFace m_fps_font;
		Texture m_cursor;		
		Ui m_ui;
		
};

#endif
