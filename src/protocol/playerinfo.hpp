#ifndef PLAYERINFO_HPP
#define PLAYERINFO_HPP

#include <string>
#include <stdint.h>

class Packet;

class PlayerInfo
{
	public:
		uint32_t playerId;
		uint32_t money;
		std::string name;

		friend Packet& operator<<(Packet& packet,const PlayerInfo& playerInfo);
		friend Packet& operator>>(Packet& packet,PlayerInfo& playerInfo);

};

#endif // PLAYERINFO_HPP

