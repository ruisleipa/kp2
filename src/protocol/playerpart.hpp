#ifndef PLAYERPART_HPP
#define PLAYERPART_HPP

#include <string>
#include <stdint.h>

class Packet;

class PlayerPart
{
	public:
		uint32_t id;
		std::string name;
		uint32_t price;
		std::string type;
		float weight;

		friend Packet& operator<<(Packet& packet,const PlayerPart& playerPart);
		friend Packet& operator>>(Packet& packet,PlayerPart& playerPart);
};

#endif // PLAYERPART_HPP

