#ifndef PROTOCOL_SHOPVEHICLE_HPP
#define PROTOCOL_SHOPVEHICLE_HPP

#include <string>
#include <stdint.h>

class Packet;

namespace Protocol
{

class ShopVehicle
{
	public:
		std::string id;
		std::string name;
		std::string imageName;
		std::string info;
		uint16_t year;
		uint32_t chassisWeight;
		uint32_t price;

		friend Packet& operator<<(Packet& packet,const ShopVehicle& shopVehicle);
		friend Packet& operator>>(Packet& packet,ShopVehicle& shopVehicle);
};

};

#endif
