#ifndef SHOPPART_HPP
#define SHOPPART_HPP

#include <string>
#include <stdint.h>

class Packet;

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

#endif // SHOPPART_HPP

