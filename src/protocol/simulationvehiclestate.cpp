#include "simulationvehiclestate.hpp"

#include "net/packet.hpp"

namespace Protocol
{

Packet& operator<<(Packet& packet,const SimulationVehicleState& state)
{
	packet << state.id;
	//packet << state.time;
	packet << state.position;
	packet << state.speed;
	packet << state.engineSpeedInRpm;
	packet << state.boostPressure;
	
	return packet;
}

Packet& operator>>(Packet& packet,SimulationVehicleState& state)
{
	packet >> state.id;
	state.time = 0;
	packet >> state.position;
	packet >> state.speed;
	packet >> state.engineSpeedInRpm;
	packet >> state.boostPressure;
	
	return packet;
}

};
