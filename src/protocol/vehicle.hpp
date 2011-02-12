#ifndef PROTOCOL_VEHICLE_HPP
#define PROTOCOL_VEHICLE_HPP

#include <string>
#include <stdint.h>

class Packet;

namespace Protocol
{

class Vehicle
{
	public:
		uint32_t id;
		std::string name;
		std::string imageName;
		std::string info;
		uint16_t year;
		uint32_t chassisWeight;
		uint32_t price;
		
		friend Packet& operator<<(Packet& packet,const Vehicle& Vehicle);
		friend Packet& operator>>(Packet& packet,Vehicle& Vehicle);
};

};
	
#endif // PROTOCOL_VEHICLE_HPP

