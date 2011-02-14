#include "setactivevehicle.hpp"

#include "net/packet.hpp"

namespace Protocol
{

Packet& operator<<(Packet& packet,const SetActiveVehicle& setActiveVehicle)
{
	packet << setActiveVehicle.id;
	
	return packet;
}

Packet& operator>>(Packet& packet,SetActiveVehicle& setActiveVehicle)
{
	packet >> setActiveVehicle.id;
	
	return packet;
}

};
