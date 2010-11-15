#include "events.hpp"

#include "graphics/window.hpp"
#include "keyevent.hpp"
#include "mouseevent.hpp"
#include "eventlistener.hpp"

#include <iostream>

void Events::processEvents()
{
	SDL_Event sdlEvent;
	EventArea eventArea(window, Vector2D(0,0), window.getSize());
	
	while(SDL_PollEvent(&sdlEvent))
	{
		if(sdlEvent.type == SDL_QUIT)
		{
			throw ExitException();
		}
		
		if(eventListener == &defaultListener)
		{
			/*
			This key is checked so that apps with no eventlistener
			can quit easily. This is handy especially when you have
			accidentally set no eventlistener in a fullscreen
			program.
			*/

			if(sdlEvent.type == SDL_KEYDOWN)
			{
				SDL_keysym& keysym = sdlEvent.key.keysym;
		
				if(keysym.sym==SDLK_ESCAPE)
					throw ExitException();
			}		
		
			continue;
		}
		
		Event* event = 0;
		
		if(sdlEvent.type == SDL_KEYDOWN)
		{
			SDL_keysym& keysym = sdlEvent.key.keysym;
		
			event = new KeyDownEvent(eventArea, keysym.unicode, keysym.sym);
		}
		else if(sdlEvent.type == SDL_KEYUP)
		{
			SDL_keysym& keysym = sdlEvent.key.keysym;
		
			event = new KeyUpEvent(eventArea, keysym.unicode, keysym.sym);
		}
		else if(sdlEvent.type == SDL_MOUSEBUTTONDOWN)
		{
			SDL_MouseButtonEvent& button = sdlEvent.button;
			Vector2D pos = Vector2D(button.x, button.y);
							
			event = new MouseDownEvent(eventArea, pos, 1 << (button.button-1));
		}
		else if(sdlEvent.type == SDL_MOUSEBUTTONUP)
		{
			SDL_MouseButtonEvent& button = sdlEvent.button;
			Vector2D pos = Vector2D(button.x, button.y);
									
			event = new MouseUpEvent(eventArea, pos, 1 << (button.button-1));
		}
		else if(sdlEvent.type == SDL_MOUSEMOTION)
		{
			SDL_MouseMotionEvent& motion = sdlEvent.motion;
			Vector2D pos = Vector2D(motion.x, motion.y);
					
			event = new MouseMoveEvent(eventArea, pos, motion.state);
		}
		
		if(event)
		{
			eventListener->handleEvent(event);
		
			delete event;
		}		
	}
}

void Events::setEventListener(EventListener* eventListener)
{
	this->eventListener=eventListener;
}

bool Events::isKeyDown(SDLKey key)
{
	uint8_t* keys=SDL_GetKeyState(0);

	return keys[key];
}

Events::Events(Window& window): 
	window(window),
	eventListener(&defaultListener)
{
	SDL_EnableUNICODE(true);
	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY,SDL_DEFAULT_REPEAT_INTERVAL);
}

Events::~Events()
{
	
}

