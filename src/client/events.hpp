#ifndef __EVENTS_HPP
#define __EVENTS_HPP

#include "eventlistener.hpp"
class Sdl;
class Graphics;

class ExitException
{

};

class Events
{
	public:
		void processEvents(Graphics& graphics);
		void resize(Graphics& graphics);
		
		void setEventListener(EventListener* event_listener);

		Events(Sdl& sdl);
		~Events();

	private:
		Sdl& m_sdl;
		EventListener* m_event_listener;	
		
		EventListener m_default_listener;	
};

#endif // __EVENTS_HPP
