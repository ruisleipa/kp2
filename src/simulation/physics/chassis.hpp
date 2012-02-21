#ifndef _CHASSIS_HPP
#define _CHASSIS_HPP

#include <iostream>
#include <string>

namespace Physics
{

class Chassis
{
	public:
		Chassis();

		float totalMass;
		float massOnRear;
		float centerOfGravityHeight;
		float length;
		float width;
		float wheelBase;
		float dragCoefficient;

};

};

#endif
