#include "racecontrolstate.hpp"

#include "net/packet.hpp"

namespace Protocol
{

Packet& operator<<(Packet& packet,const RaceControlState& state)
{
	packet << state.throttle;
	packet << state.clutch;
	packet << state.brake;
	
	return packet;
}

Packet& operator>>(Packet& packet,RaceControlState& state)
{
	packet >> state.throttle;
	packet >> state.clutch;
	packet >> state.brake;
		
	return packet;
}

};
