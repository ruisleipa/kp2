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
		void setEventListener(EventListener* event_listener);
		
		bool isKeyDown(SDLKey key);

		Events(Window& window);
		~Events();

	private:
		Window& window;
		
		EventListener* m_event_listener;	
		
		EventListener m_default_listener;	
};

#endif // EVENTS_HPP
