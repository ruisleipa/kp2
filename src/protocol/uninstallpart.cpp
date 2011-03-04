#include "uninstallpart.hpp"

#include "net/packet.hpp"

namespace Protocol
{

Packet& operator<<(Packet& packet,const UninstallPart& command)
{
	packet << command.id;
	
	return packet;
}

Packet& operator>>(Packet& packet,UninstallPart& command)
{
	packet >> command.id;
	
	return packet;
}

};
