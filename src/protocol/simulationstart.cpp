#include "simulationstart.hpp"

#include "net/packet.hpp"

namespace Protocol
{

Packet& operator<<(Packet& packet,const SimulationStart& state)
{
	return packet;
}

Packet& operator>>(Packet& packet,SimulationStart& state)
{
	return packet;
}

};
