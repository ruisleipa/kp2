#ifndef PROTOCOL_CONTROLSTATE_HPP
#define PROTOCOL_CONTROLSTATE_HPP

#include <stdint.h>

class Packet;

namespace Protocol
{

class ControlState
{
	public:
		bool ignition;
		float throttle;
		float clutch;
		float brake;
		bool gearUp;
		bool gearDown;
		
		friend Packet& operator<<(Packet& packet,const ControlState& state);
		friend Packet& operator>>(Packet& packet,ControlState& state);

};

};

#endif
