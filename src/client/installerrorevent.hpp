#ifndef CLIENT_INSTALLERROREVENT_HPP
#define CLIENT_INSTALLERROREVENT_HPP

#include "events/event.hpp"

#include <string>

class InstallErrorEvent: public Event
{
	public:
		std::string error;
};

#endif
