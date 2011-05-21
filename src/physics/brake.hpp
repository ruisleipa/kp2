#ifndef BRAKE_HPP
#define BRAKE_HPP

namespace Physics
{

class Brake
{
	public:
		float getTorque(float usage, float disc_speed);
		
		Brake(float coefficientOfFriction, float maxTorque);

	private:
		float coefficientOfFriction;
		float maxTorque;

};

};

#endif
