#ifndef PROTOCOL_PERFORMANCEDATA_HPP
#define PROTOCOL_PERFORMANCEDATA_HPP

#include "utils/curve.hpp"

namespace Protocol
{

class PerformanceData
{
	public:
		Curve torque;
		Curve power;
		Curve intake;
		Curve exhaust;

		friend Packet& operator<<(Packet& packet,const PerformanceData& performanceData);
		friend Packet& operator>>(Packet& packet,PerformanceData& performanceData);
};
	
};

#endif

