#include "vehicle.hpp"

#include "net/packet.hpp"

namespace Protocol
{

Packet& operator<<(Packet& packet,const Protocol::Vehicle& vehicle)
{
	packet << vehicle.name;
	packet << vehicle.imageName;
	packet << vehicle.info;
	packet << vehicle.year;
	packet << vehicle.chassisWeight;
	packet << vehicle.totalWeight;
	packet << vehicle.price;
	packet << vehicle.parts;
	
	return packet;
}

Packet& operator>>(Packet& packet,Protocol::Vehicle& vehicle)
{
	packet >> vehicle.name;
	packet >> vehicle.imageName;
	packet >> vehicle.info;
	packet >> vehicle.year;
	packet >> vehicle.chassisWeight;
	packet >> vehicle.totalWeight;
	packet >> vehicle.price;
	packet >> vehicle.parts;	
	
	return packet;
}

};
