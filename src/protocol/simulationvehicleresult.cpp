#include "simulationvehicleresult.hpp"

#include "net/packet.hpp"

namespace Protocol
{

Packet& operator<<(Packet& packet,const SimulationVehicleResult& result)
{
	packet << result.reactionTime;
	packet << result.elapsedTime;
	packet << result.totalTime;
	packet << result.topSpeed;
	
	return packet;
}

Packet& operator>>(Packet& packet,SimulationVehicleResult& result)
{
	packet >> result.reactionTime;
	packet >> result.elapsedTime;
	packet >> result.totalTime;
	packet >> result.topSpeed;
	
	return packet;
}

};
