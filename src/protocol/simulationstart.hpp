#ifndef PROTOCOL_SIMULATIONSTART_HPP
#define PROTOCOL_SIMULATIONSTART_HPP

#include <stdint.h>

class Packet;

namespace Protocol
{

class SimulationStart
{
	public:
		friend Packet& operator<<(Packet& packet,const SimulationStart& start);
		friend Packet& operator>>(Packet& packet,SimulationStart& start);

};

};

#endif
