#ifndef PROTOCOL_SIMULATIONVEHICLESTATE_HPP
#define PROTOCOL_SIMULATIONVEHICLESTATE_HPP

#include <stdint.h>

class Packet;

namespace Protocol
{

class SimulationVehicleState
{
	public:
		uint16_t id;
		float time;
		float position;
		float speed;
		float engineSpeedInRpm;
		float boostPressure;
		float leftTireSlipRatio;
		float rightTireSlipRatio;
	
		friend Packet& operator<<(Packet& packet,const SimulationVehicleState& state);
		friend Packet& operator>>(Packet& packet,SimulationVehicleState& state);

};

};

#endif
