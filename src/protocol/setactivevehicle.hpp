#ifndef PROTOCOL_SETACTIVEVEHICLE_HPP
#define PROTOCOL_SETACTIVEVEHICLE_HPP

#include <string>

class Packet;

namespace Protocol
{

class SetActiveVehicle
{
	public:
		uint32_t id;

		friend Packet& operator<<(Packet& packet,const SetActiveVehicle& setActiveVehicle);
		friend Packet& operator>>(Packet& packet,SetActiveVehicle& setActiveVehicle);

};

};

#endif
