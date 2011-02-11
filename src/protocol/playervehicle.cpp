#include "playervehicle.hpp"

#include "net/packet.hpp"

Packet& operator<<(Packet& packet,const PlayerVehicle& playerVehicle)
{
	packet << playerVehicle.id;
	packet << playerVehicle.name;
	packet << playerVehicle.imageName;
	packet << playerVehicle.info;
	packet << playerVehicle.year;
	packet << playerVehicle.chassisWeight;
	packet << playerVehicle.price;
	
	return packet;
}

Packet& operator>>(Packet& packet,PlayerVehicle& playerVehicle)
{
	packet >> playerVehicle.id;
	packet >> playerVehicle.name;
	packet >> playerVehicle.imageName;
	packet >> playerVehicle.info;
	packet >> playerVehicle.year;
	packet >> playerVehicle.chassisWeight;
	packet >> playerVehicle.price;
	
	return packet;
}