#include "players.hpp"

#include "net/packet.hpp"

size_t Players::getPlayerCount()
{
	return players.size();
}

PlayerInfo Players::getPlayer(size_t index)
{
	return players.at(index);
}

void Players::addPlayer(const PlayerInfo& playerInfo)
{
	players.push_back(playerInfo);
}

Packet& operator<<(Packet& packet,const Players& players)
{
	packet << uint32_t(players.players.size());
	
	for(size_t i = 0; i < players.players.size(); ++i)
	{
		packet << players.players[i];
	}
	
	return packet;
}

Packet& operator>>(Packet& packet,Players& players)
{
	uint32_t playerCount;
	
	packet >> playerCount;
	
	for(size_t i = 0; i < playerCount; ++i)
	{
		PlayerInfo playerInfo;
		
		packet >> playerInfo;
		
		players.players.push_back(playerInfo);
	}
		
	return packet;
}