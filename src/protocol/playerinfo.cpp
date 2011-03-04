#include "playerinfo.hpp"

#include <iostream>

#include "net/packet.hpp"

namespace Protocol
{

Packet& operator<<(Packet& packet,const PlayerInfo& playerInfo)
{
	packet << playerInfo.money;
	packet << playerInfo.name;
	
	return packet;
}

Packet& operator>>(Packet& packet,PlayerInfo& playerInfo)
{
	packet >> playerInfo.money;
	packet >> playerInfo.name;
		
	return packet;
}

};
