#ifndef PROTOCOL_RACESTART_HPP
#define PROTOCOL_RACESTART_HPP

#include <stdint.h>
#include <string>

class Packet;

namespace Protocol
{

class SimulationVehicleData
{
	public:
		uint16_t id;
		std::string imageName;
		float width;
	
		friend Packet& operator<<(Packet& packet,const SimulationVehicleData& data);
		friend Packet& operator>>(Packet& packet,SimulationVehicleData& data);

};

};

#endif
