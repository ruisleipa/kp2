#ifndef PROTOCOL_RACESTART_HPP
#define PROTOCOL_RACESTART_HPP

#include <stdint.h>

class Packet;

namespace Protocol
{

class RaceStart
{
	public:
		friend Packet& operator<<(Packet& packet,const RaceStart& raceStart);
		friend Packet& operator>>(Packet& packet,RaceStart& raceStart);

};

};

#endif
