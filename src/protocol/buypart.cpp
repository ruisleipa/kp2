#include "buypart.hpp"

#include "net/packet.hpp"

namespace Protocol
{

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

};
