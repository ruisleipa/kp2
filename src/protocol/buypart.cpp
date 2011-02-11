#include "buypart.hpp"

#include "net/packet.hpp"

Packet& operator<<(Packet& packet,const BuyPart& buyPart)
{
	packet << buyPart.id;
	
	return packet;
}

Packet& operator>>(Packet& packet,BuyPart& buyPart)
{
	packet >> buyPart.id;
	
	return packet;
}