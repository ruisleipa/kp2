#include "brake.hpp"

#include <cmath>
#include "math_tools.hpp"

namespace Physics
{

float Brake::getTorque(float discSpeed)
{
	float absoluteTorque = usage * coefficientOfFriction * fabs(discSpeed);
	
	if (absoluteTorque > maxTorque)
		absoluteTorque = maxTorque;
		
	return absoluteTorque * -sgn(discSpeed);
}

void Brake::setUsage(float usage)
{
	this->usage = usage;
}

Brake::Brake(float coefficientOfFriction, float maxTorque):
	coefficientOfFriction(coefficientOfFriction),
	maxTorque(maxTorque),
	usage(0)
{

}

};
