#include "racestate.hpp"

#include "net/packet.hpp"

namespace Protocol
{

Packet& operator<<(Packet& packet,const RaceState& state)
{
	packet << state.time;
	packet << state.position;
	packet << state.speed;
	packet << state.engineSpeedInRpm;
	packet << state.boostPressure;
	
	return packet;
}

Packet& operator>>(Packet& packet,RaceState& state)
{
	packet >> state.time;
	packet >> state.position;
	packet >> state.speed;
	packet >> state.engineSpeedInRpm;
	packet >> state.boostPressure;
	
	return packet;
}

};
