#ifndef BRAKE_HPP
#define BRAKE_HPP

namespace Physics
{

class Brake
{
	public:
		float getTorque(float disc_speed);
		
		void setUsage(float usage);
		
		Brake(float coefficientOfFriction, float maxTorque);

	private:
		float coefficientOfFriction;
		float maxTorque;
		float usage;

};

};

#endif
