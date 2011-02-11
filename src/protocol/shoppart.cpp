#include "shoppart.hpp"

#include "net/packet.hpp"

Packet& operator<<(Packet& packet,const ShopPart& shopPart)
{
	packet << shopPart.id;
	packet << shopPart.name;
	packet << shopPart.price;
	packet << shopPart.type;
	packet << shopPart.weight;
	
	return packet;
}

Packet& operator>>(Packet& packet,ShopPart& shopPart)
{
	packet >> shopPart.id;
	packet >> shopPart.name;
	packet >> shopPart.price;
	packet >> shopPart.type;
	packet >> shopPart.weight;
	
	return packet;
}