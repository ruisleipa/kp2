#include "performancedata.hpp"

#include "net/packet.hpp"

namespace Protocol
{

Packet& operator<<(Packet& packet,const PerformanceData& performanceData)
{
	packet << performanceData.torque;
	packet << performanceData.power;
	
	return packet;
}

Packet& operator>>(Packet& packet, PerformanceData& performanceData)
{
	packet >> performanceData.torque;
	packet >> performanceData.power;
	
	return packet;
}

};
