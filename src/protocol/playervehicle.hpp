#ifndef PLAYERVEHICLE_HPP
#define PLAYERVEHICLE_HPP

#include <string>
#include <stdint.h>

class Packet;

class PlayerVehicle
{
	public:
		uint32_t id;
		std::string name;
		std::string imageName;
		std::string info;
		uint16_t year;
		uint32_t chassisWeight;
		uint32_t price;
		
		friend Packet& operator<<(Packet& packet,const PlayerVehicle& playerVehicle);
		friend Packet& operator>>(Packet& packet,PlayerVehicle& playerVehicle);
};

#endif // PLAYERVEHICLE_HPP

