#ifndef CLIENT_RACESTATEEVENT_HPP
#define CLIENT_RACESTATEEVENT_HPP

#include "events/event.hpp"
#include "protocol/racestate.hpp"

class RaceStateEvent: public Event
{
	public:
		Protocol::RaceState state;
};

#endif
