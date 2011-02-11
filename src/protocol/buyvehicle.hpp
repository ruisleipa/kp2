#ifndef PROTOCOL_BUYVEHICLE_HPP
#define PROTOCOL_BUYVEHICLE_HPP

#include <string>

class Packet;

class BuyVehicle
{
	public:
		std::string id;

		friend Packet& operator<<(Packet& packet,const BuyVehicle& buyVehicle);
		friend Packet& operator>>(Packet& packet,BuyVehicle& buyVehicle);

};

#endif // PROTOCOL_BUYVEHICLE_HPP

