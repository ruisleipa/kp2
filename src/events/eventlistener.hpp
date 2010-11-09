#ifndef EVENTLISTENER_HPP
#define EVENTLISTENER_HPP

#include "keyevent.hpp"
#include "mouseevent.hpp"

class EventListener
{
	public:
		virtual void handleEvent(Event* event);
};

#endif // KEYEVENT_HPP
