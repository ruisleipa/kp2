#include "brake.hpp"

#include <cmath>
#include "math_tools.hpp"

float Brake::getTorque(float usage, float discSpeed)
{
	float absoluteTorque = usage * coefficientOfFriction * fabs(discSpeed);
	
	if (absoluteTorque > maxTorque)
		absoluteTorque = maxTorque;
		
	return -absoluteTorque * sgn(discSpeed);
}

Brake::Brake(float coefficientOfFriction, float maxTorque):
	coefficientOfFriction(coefficientOfFriction),
	maxTorque(maxTorque)
{	

}
