#ifndef __EVENTS_HPP
#define __EVENTS_HPP

#include "keyevent.hpp"
#include "mouseevent.hpp"

#include "eventlistener.hpp"

class ExitException
{

};

class Events
{
	public:
		static Events& getInstance();

		void processEvents();
		
		void setEventListener(EventListener* event_listener);

		~Events();

	private:
		Events();
		
		EventListener* m_event_listener;
		
		
};

#endif // __EVENTS_HPP
