#ifndef PROTOCOL_RACESTATE_HPP
#define PROTOCOL_RACESTATE_HPP

#include <stdint.h>

class Packet;

namespace Protocol
{

class RaceState
{
	public:
		float time;
		float position;
		float speed;
		float engineSpeedInRpm;
		float boostPressure;
	
		friend Packet& operator<<(Packet& packet,const RaceState& raceState);
		friend Packet& operator>>(Packet& packet,RaceState& raceState);

};

};

#endif
