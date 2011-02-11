#include "buyvehicle.hpp"

#include "net/packet.hpp"

Packet& operator<<(Packet& packet,const BuyVehicle& buyVehicle)
{
	packet << buyVehicle.id;
	
	return packet;
}

Packet& operator>>(Packet& packet,BuyVehicle& buyVehicle)
{
	packet >> buyVehicle.id;
	
	return packet;
}