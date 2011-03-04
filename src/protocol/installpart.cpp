#include "installpart.hpp"

#include "net/packet.hpp"

namespace Protocol
{

Packet& operator<<(Packet& packet,const InstallPart& command)
{
	packet << command.id;
	
	return packet;
}

Packet& operator>>(Packet& packet,InstallPart& command)
{
	packet >> command.id;
	
	return packet;
}

};
