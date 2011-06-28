#include "simulationvehicledata.hpp"

#include "net/packet.hpp"

namespace Protocol
{

Packet& operator<<(Packet& packet,const SimulationVehicleData& data)
{
	packet << data.id;
	packet << data.imageName;
	packet << data.width;
	
	return packet;
}

Packet& operator>>(Packet& packet,SimulationVehicleData& data)
{
	packet >> data.id;
	packet >> data.imageName;
	packet >> data.width;
	
	return packet;
}

};
