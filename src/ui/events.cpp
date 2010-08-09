#include "events.hpp"

#include "graphics.hpp"
#include "keyevent.hpp"
#include "mouseevent.hpp"
#include "eventlistener.hpp"

#include <iostream>

void Events::setEventListener(EventListener* event_listener)
{
	m_event_listener=event_listener;
}

bool Events::isKeyDown(SDLKey key)
{
	uint8_t* keys=SDL_GetKeyState(0);

	return keys[key];
}

void Events::processEvents(Graphics& graphics)
{
	SDL_Event sdl_event;

	while(SDL_PollEvent(&sdl_event))
	{
		if(sdl_event.type == SDL_QUIT)
		{
			throw ExitException();
		}
		
		if(m_event_listener == &m_default_listener)
		{
			/*
			This key is checked so that apps with no eventlistener
			can quit easily. This is handy especially when you have
			accidentally set no eventlistener in a fullscreen
			program.
			*/		
			if(sdl_event.type == SDL_KEYDOWN)
			{
				SDL_keysym& keysym = sdl_event.key.keysym;
		
				if(keysym.sym==SDLK_ESCAPE)
					throw ExitException();
			}		
		
			continue;
		}
		
		if(sdl_event.type == SDL_KEYDOWN)
		{
			SDL_keysym& keysym = sdl_event.key.keysym;
		
			KeyEvent event(keysym.unicode, keysym.sym);
			
			m_event_listener->doKeyDown(event);
		}
		else if(sdl_event.type == SDL_KEYUP)
		{
			SDL_keysym& keysym = sdl_event.key.keysym;
		
			KeyEvent event(keysym.unicode, keysym.sym);
			
			m_event_listener->doKeyUp(event);
		}
		else if(sdl_event.type == SDL_MOUSEBUTTONDOWN)
		{
			SDL_MouseButtonEvent& button = sdl_event.button;
			Vector2D pos=Vector2D(button.x, button.y);
			pos/=graphics.getDisplaySize();
							
			MouseEvent event(pos, 1 << (button.button-1));
			
			m_event_listener->doMouseDown(event);
		}
		else if(sdl_event.type == SDL_MOUSEBUTTONUP)
		{
			SDL_MouseButtonEvent& button = sdl_event.button;
			Vector2D pos=Vector2D(button.x, button.y);
			pos/=graphics.getDisplaySize();
									
			MouseEvent event(pos, 1 << (button.button-1));
			
			m_event_listener->doMouseUp(event);
		}
		else if(sdl_event.type == SDL_MOUSEMOTION)
		{
			SDL_MouseMotionEvent& motion = sdl_event.motion;
			Vector2D pos=Vector2D(motion.x, motion.y);
			pos/=graphics.getDisplaySize();
					
			MouseEvent event(pos, motion.state);
			
			m_event_listener->doMouseMove(event);
		}
		else if(sdl_event.type == SDL_VIDEORESIZE)
		{
			SDL_ResizeEvent& resize = sdl_event.resize;
		
			graphics.resize(Vector2D(resize.w,resize.h));
		}
	}
}

void Events::resize(Graphics& graphics)
{
	m_event_listener->doResize(graphics);
}

Events::Events(Sdl& sdl): 
	m_sdl(sdl), 
	m_event_listener(&m_default_listener)
{
	SDL_EnableUNICODE(true);
	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY,SDL_DEFAULT_REPEAT_INTERVAL);
}

Events::~Events()
{
	
}
