#include "playerpart.hpp"

#include "net/packet.hpp"

Packet& operator<<(Packet& packet,const PlayerPart& playerPart)
{
	packet << playerPart.id;
	packet << playerPart.name;
	packet << playerPart.price;
	packet << playerPart.type;
	packet << playerPart.weight;
	
	return packet;
}

Packet& operator>>(Packet& packet,PlayerPart& playerPart)
{
	packet >> playerPart.id;
	packet >> playerPart.name;
	packet >> playerPart.price;
	packet >> playerPart.type;
	packet >> playerPart.weight;
	
	return packet;
}