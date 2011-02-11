#ifndef PLAYERS_HPP
#define PLAYERS_HPP

#include <vector>

#include "protocol/playerinfo.hpp"

class Packet;

class Players
{
	public:
		size_t getPlayerCount();
		PlayerInfo getPlayer(size_t index);
		void addPlayer(const PlayerInfo& playerInfo);
		
		friend Packet& operator<<(Packet& packet,const Players& players);
		friend Packet& operator>>(Packet& packet,Players& players);
		
	private:
		std::vector<PlayerInfo> players;

};

#endif // PLAYERS_HPP

