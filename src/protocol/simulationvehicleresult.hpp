#ifndef PROTOCOL_SIMULATIONVEHICLERESULT_HPP
#define PROTOCOL_SIMULATIONVEHICLERESULT_HPP

#include <stdint.h>

class Packet;

namespace Protocol
{

class SimulationVehicleResult
{
	public:
		float reactionTime;
		float elapsedTime;
		float totalTime;
		float topSpeed;
	
		friend Packet& operator<<(Packet& packet,const SimulationVehicleResult& result);
		friend Packet& operator>>(Packet& packet,SimulationVehicleResult& result);

};

};

#endif
