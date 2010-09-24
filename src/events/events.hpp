#ifndef EVENTS_HPP
#define EVENTS_HPP

#include "eventlistener.hpp"
#include "utils/sdl.hpp"

class Window;

class ExitException
{

};

class Events
{
	public:
		void processEvents();
		void setEventListener(EventListener* eventListener);
		
		bool isKeyDown(SDLKey key);

		Events(Window& window);
		~Events();

	private:
		Window& window;
		
		EventListener* eventListener;	
		
		EventListener defaultListener;	
};

#endif // EVENTS_HPP
