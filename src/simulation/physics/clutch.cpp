#include "clutch.hpp"
#include "math_tools.hpp"

#include <algorithm>
#include <cmath>

namespace Physics
{

float Clutch::calculateTorqueTransferToTransmission(float engineSpeed, float gearboxSpeed)
{
	float slipRatio = calculateSlipRatio(engineSpeed, gearboxSpeed);
	
	float normalized = slipRatio * 1.0;
	
	if(normalized > 1.0)
		normalized = 1.0;
	
	if(normalized < -1.0)
		normalized = -1.0;
	
	return normalized * maxTorque * pow(usage, 3);
}

float Clutch::calculateSlipRatio(float engineSpeed, float gearboxSpeed)
{
	float slipRatio;
	
	if(gearboxSpeed == 0.0)
		slipRatio = 10000.0;
	else
		slipRatio = -(gearboxSpeed - engineSpeed) / std::max(gearboxSpeed, engineSpeed);
	
	return slipRatio;
}

void Clutch::setUsage(float usage)
{
	this->usage = usage;
}

float Clutch::getUsage()
{
	return usage;
}

Clutch::Clutch(float maxTorque):
	maxTorque(maxTorque),
	usage(0)
{

}

};

