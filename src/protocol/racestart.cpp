#include "racestart.hpp"

#include "net/packet.hpp"

namespace Protocol
{

Packet& operator<<(Packet& packet,const RaceStart& state)
{
	return packet;
}

Packet& operator>>(Packet& packet,RaceStart& state)
{
	return packet;
}

};
