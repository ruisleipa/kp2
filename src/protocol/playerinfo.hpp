#ifndef PROTOCOL_PLAYERINFO_HPP
#define PROTOCOL_PLAYERINFO_HPP

#include <string>
#include <stdint.h>

class Packet;

namespace Protocol
{

class PlayerInfo
{
	public:
		uint32_t playerId;
		uint32_t money;
		std::string name;

		friend Packet& operator<<(Packet& packet,const PlayerInfo& playerInfo);
		friend Packet& operator>>(Packet& packet,PlayerInfo& playerInfo);

};

};

#endif
