#include "events.hpp"

#include "sdl.hpp"
#include "graphics.hpp"

Events& Events::getInstance()
{
	static Events instance;

	return instance;
}

void Events::setEventListener(EventListener* event_listener)
{
	m_event_listener=event_listener;
}

void Events::processEvents()
{
	SDL_Event sdl_event;

	while(SDL_PollEvent(&sdl_event))
	{
		if(sdl_event.type == SDL_QUIT)
		{
			throw ExitException();
		}
		
		if(m_event_listener == 0)
			continue;
		
		if(sdl_event.type == SDL_KEYDOWN)
		{
			SDL_keysym& keysym = sdl_event.key.keysym;
		
			if(keysym.sym==SDLK_ESCAPE)
				exit(0);
		
			KeyEvent event(keysym.unicode, keysym.sym);
			
			m_event_listener->keyDown(event);
		}
		else if(sdl_event.type == SDL_KEYUP)
		{
			SDL_keysym& keysym = sdl_event.key.keysym;
		
			KeyEvent event(keysym.unicode, keysym.sym);
			
			m_event_listener->keyUp(event);
		}
		else if(sdl_event.type == SDL_MOUSEBUTTONDOWN)
		{
			SDL_MouseButtonEvent& button = sdl_event.button;
			Vector2D pos(button.x, button.y);
					
			MouseEvent event(pos, 1 << (button.button-1));
			
			m_event_listener->mouseDown(event);
		}
		else if(sdl_event.type == SDL_MOUSEBUTTONUP)
		{
			SDL_MouseButtonEvent& button = sdl_event.button;
			Vector2D pos(button.x, button.y);
					
			MouseEvent event(pos, 1 << (button.button-1));
			
			m_event_listener->mouseUp(event);
		}
		else if(sdl_event.type == SDL_MOUSEMOTION)
		{
			SDL_MouseMotionEvent& motion = sdl_event.motion;
			Vector2D pos(motion.x, motion.y);
					
			MouseEvent event(pos, motion.state);
			
			m_event_listener->mouseMove(event);
		}
		else if(sdl_event.type == SDL_VIDEORESIZE)
		{
			SDL_ResizeEvent& resize = sdl_event.resize;
		
			Graphics::getInstance().resize(Vector2D(resize.w,resize.h));
		}
	}
}

Events::Events()
{
	//make sure SDL is initalized
	Sdl::getInstance();

	SDL_EnableUNICODE(true);
	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY,SDL_DEFAULT_REPEAT_INTERVAL);
}

Events::~Events()
{
	
}

