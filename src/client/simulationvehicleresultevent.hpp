#ifndef CLIENT_SIMULATIONVEHICLERESULTEVENT_HPP
#define CLIENT_SIMULATIONVEHICLERESULTEVENT_HPP

#include "events/event.hpp"
#include "protocol/simulationvehicleresult.hpp"

class SimulationVehicleResultEvent: public Event
{
	public:
		Protocol::SimulationVehicleResult result;
};

#endif
