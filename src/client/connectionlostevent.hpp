#ifndef CLIENT_CONNECTIONLOSTEVENT_HPP
#define CLIENT_CONNECTIONLOSTEVENT_HPP

#include "events/event.hpp"

#include <string>

class ConnectionLostEvent: public Event
{
	public:
		std::string error;
};

#endif
