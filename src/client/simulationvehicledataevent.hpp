#ifndef CLIENT_SIMULATIONVEHICLEDATAEVENT_HPP
#define CLIENT_SIMULATIONVEHICLEDATAEVENT_HPP

#include "events/event.hpp"
#include "protocol/simulationvehicledata.hpp"

class SimulationVehicleDataEvent: public Event
{
	public:
		Protocol::SimulationVehicleData data;
};

#endif
