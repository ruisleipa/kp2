#ifndef PROTOCOL_SHOPPART_HPP
#define PROTOCOL_SHOPPART_HPP

#include <string>
#include <stdint.h>

class Packet;

namespace Protocol
{

class ShopPart
{
	public:
		std::string id;
		std::string name;
		uint32_t price;
		std::string type;
		float weight;

		friend Packet& operator<<(Packet& packet,const ShopPart& shopPart);
		friend Packet& operator>>(Packet& packet,ShopPart& shopPart);
};

};

#endif

