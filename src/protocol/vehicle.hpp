#ifndef PROTOCOL_VEHICLE_HPP
#define PROTOCOL_VEHICLE_HPP

#include "idtypes.hpp"
#include "part.hpp"
#include "collection.hpp"

#include <string>
#include <stdint.h>

class Packet;

namespace Protocol
{

class Vehicle
{
	public:
		std::string name;
		std::string imageName;
		std::string info;
		uint16_t year;
		uint32_t chassisWeight;
		uint32_t totalWeight;
		uint32_t price;
		
		Protocol::Collection<Protocol::PartId, Protocol::Part> parts;
		
		friend Packet& operator<<(Packet& packet,const Vehicle& Vehicle);
		friend Packet& operator>>(Packet& packet,Vehicle& Vehicle);
};

};
	
#endif // PROTOCOL_VEHICLE_HPP

