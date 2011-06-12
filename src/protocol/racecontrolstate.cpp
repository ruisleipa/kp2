#include "racecontrolstate.hpp"

#include "net/packet.hpp"

namespace Protocol
{

Packet& operator<<(Packet& packet,const RaceControlState& state)
{
	packet << uint16_t(state.ignition);
	packet << state.throttle;
	packet << state.clutch;
	packet << state.brake;
	packet << uint16_t(state.gearUp);
	packet << uint16_t(state.gearDown);
	
	return packet;
}

Packet& operator>>(Packet& packet,RaceControlState& state)
{
	uint16_t ignition;
	uint16_t gearUp;
	uint16_t gearDown;
	
	packet >> ignition;
	packet >> state.throttle;
	packet >> state.clutch;
	packet >> state.brake;
	packet >> gearUp;
	packet >> gearDown;
	
	state.ignition = ignition;
	state.gearUp = gearUp;
	state.gearDown = gearDown;
		
	return packet;
}

};
