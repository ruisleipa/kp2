#ifndef CLIENT_SIMULATIONVEHICLESTATEEVENT_HPP
#define CLIENT_SIMULATIONVEHICLESTATEEVENT_HPP

#include "events/event.hpp"
#include "protocol/simulationvehiclestate.hpp"

class SimulationVehicleStateEvent: public Event
{
	public:
		Protocol::SimulationVehicleState state;
};

#endif
