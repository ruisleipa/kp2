#include "part.hpp"

#include "net/packet.hpp"

namespace Protocol
{

Packet& operator<<(Packet& packet,const Protocol::Part& part)
{
	packet << part.id;
	packet << part.name;
	packet << part.price;
	packet << part.type;
	packet << part.weight;
	
	return packet;
}

Packet& operator>>(Packet& packet,Protocol::Part& part)
{
	packet >> part.id;
	packet >> part.name;
	packet >> part.price;
	packet >> part.type;
	packet >> part.weight;
	
	return packet;
}

};
