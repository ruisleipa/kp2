#include "clutch.hpp"
#include "math_tools.hpp"

#include <cmath>

float Clutch::getTorque(float inputSpeed, float outputSpeed)
{
	return pow(usage, 3) * maxTorque * sgn(inputSpeed - outputSpeed);
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

