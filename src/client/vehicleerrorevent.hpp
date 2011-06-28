#ifndef CLIENT_VEHICLEERROREVENT_HPP
#define CLIENT_VEHICLEERROREVENT_HPP

#include "events/event.hpp"

#include <string>

class VehicleErrorEvent: public Event
{
	public:
		std::string error;
};

#endif
