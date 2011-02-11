#ifndef SHOPVEHICLE_HPP
#define SHOPVEHICLE_HPP

#include <string>
#include <stdint.h>

class Packet;

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

#endif // SHOPVEHICLE_HPP

