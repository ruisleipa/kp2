#include "setname.hpp"

#include "net/packet.hpp"

Packet& operator<<(Packet& packet,const SetName& setName)
{
	packet << setName.name;
	
	return packet;
}

Packet& operator>>(Packet& packet,SetName& setName)
{
	packet >> setName.name;
	
	return packet;
}