#include "clutch.hpp"
#include "math_tools.hpp"

#include <algorithm>
#include <cmath>

namespace Physics
{

float Clutch::getTorque(float inputSpeed, float outputSpeed)
{
	return pow(usage, 3) * maxTorque * sgn(inputSpeed - outputSpeed);

	float absDiff = abs(inputSpeed - outputSpeed);
	
	float maxTorqueAtDiff = 500;
	
	float ratio = std::min(absDiff / maxTorqueAtDiff, 1.0f);
	
	return usage * maxTorque * sgn(inputSpeed - outputSpeed) * ratio;
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

