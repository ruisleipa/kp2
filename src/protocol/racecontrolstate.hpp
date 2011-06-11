#ifndef PROTOCOL_RACECONTROLSTATE_HPP
#define PROTOCOL_RACECONTROLSTATE_HPP

#include <stdint.h>

class Packet;

namespace Protocol
{

class RaceControlState
{
	public:
		bool ignition;
		float throttle;
		float clutch;
		float brake;
		bool gearUp;
		bool gearDown;
		
		friend Packet& operator<<(Packet& packet,const RaceControlState& state);
		friend Packet& operator>>(Packet& packet,RaceControlState& state);

};

};

#endif
