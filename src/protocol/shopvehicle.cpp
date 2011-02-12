#include "shopvehicle.hpp"

#include "net/packet.hpp"

namespace Protocol
{

Packet& operator<<(Packet& packet,const ShopVehicle& shopVehicle)
{
	packet << shopVehicle.id;
	packet << shopVehicle.name;
	packet << shopVehicle.imageName;
	packet << shopVehicle.info;
	packet << shopVehicle.year;
	packet << shopVehicle.chassisWeight;
	packet << shopVehicle.price;
	
	return packet;
}

Packet& operator>>(Packet& packet,ShopVehicle& shopVehicle)
{
	packet >> shopVehicle.id;
	packet >> shopVehicle.name;
	packet >> shopVehicle.imageName;
	packet >> shopVehicle.info;
	packet >> shopVehicle.year;
	packet >> shopVehicle.chassisWeight;
	packet >> shopVehicle.price;
	
	return packet;
}

};
