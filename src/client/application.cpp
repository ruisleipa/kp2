#include "application.hpp"

#include "shared/string.hpp"

/* in milliseconds */
const float FPS_UPDATE_RATE=1000.0;

void Application::enterMainLoop()
{
	//loadCursor();

	int frames=0;
	int time=SDL_GetTicks();
	float fps=0;
		
	while(1)
	{
		try
		{
			m_events.processEvents(m_graphics);
		}
		catch(ExitException)
		{
			break;			
		}
		
		m_connection.processMessages();			
			
		m_graphics.enterGuiMode();
		
		m_ui.draw();

		Color(1,1,1).apply();
		m_fps_font.draw(convertToWideString((int)fps),Vector2D(0.75,0.001),0.05);		
		
		//drawCursor();
		
		m_graphics.exitGuiMode();
						
		SDL_GL_SwapBuffers();
		
		frames++;
		
		if(SDL_GetTicks()-FPS_UPDATE_RATE>=time)
		{
			fps=static_cast<float>(frames)/(static_cast<float>(SDL_GetTicks()-time)/1000.0);
			time=SDL_GetTicks();
			frames=0;
		}
	}
}

void Application::loadCursor()
{
	m_cursor.load("data/images/cursor.png");
	m_cursor.setFilter(NEAREST);
	
	SDL_ShowCursor(false);
}

void Application::drawCursor()
{
	int x,y;
	
	SDL_GetMouseState(&x,&y);
		
	Vector2D cursorpos=Vector2D(x,y)/m_graphics.getDisplaySize();
	Vector2D cursorsize=Vector2D(32,32)/m_graphics.getDisplaySize();
		
	m_cursor.draw(cursorpos,cursorsize);
}

Application::Application():
	m_sdl(),
	m_events(m_sdl),
	m_graphics(m_sdl,m_events),
	m_connection(),
	m_fps_font(m_graphics),
	m_cursor(),
	m_ui(m_events,m_graphics)	
{
	m_fps_font.load("data/fonts/freesans.ttf",32);
}

Application::~Application()
{

}
