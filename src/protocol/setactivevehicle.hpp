#ifndef PROTOCOL_SETACTIVEVEHICLE_HPP
#define PROTOCOL_SETACTIVEVEHICLE_HPP

#include <string>

#include "idtypes.hpp"

class Packet;

namespace Protocol
{

class SetActiveVehicle
{
	public:
		Protocol::VehicleId id;

		friend Packet& operator<<(Packet& packet,const SetActiveVehicle& setActiveVehicle);
		friend Packet& operator>>(Packet& packet,SetActiveVehicle& setActiveVehicle);

};

};

#endif
