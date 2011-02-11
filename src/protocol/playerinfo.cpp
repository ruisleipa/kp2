#include "playerinfo.hpp"

#include <iostream>

#include "net/packet.hpp"

Packet& operator<<(Packet& packet,const PlayerInfo& playerInfo)
{
	packet << playerInfo.playerId;
	packet << playerInfo.money;
	packet << playerInfo.name;
	
	return packet;
}

Packet& operator>>(Packet& packet,PlayerInfo& playerInfo)
{
	packet >> playerInfo.playerId;
	packet >> playerInfo.money;
	packet >> playerInfo.name;
		
	return packet;
}