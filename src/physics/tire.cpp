#include "tire.hpp"
#include "math_tools.hpp"

Tire::Tire(float mass, float radius, float rollingResistanceCoefficient):
	slipRatio(0),
	radius(0),
	inertia(0),
	rollingResistanceCoefficient(0)
{
	inertia = 0.5f * mass * radius * radius;
}

double Tire::getRadius()
{
	return radius;
}

double Tire::getInertia()
{
	return inertia;
}

double Tire::getFriction(double load)
{
	// These are magic constants that produce somewhat nice values
	const float a = 9.00;
	const float b = 16.00;
	const float p = 1.40;
	
	float coefficient = (slipRatio * b) / (1.0 + pow(fabs(a * slipRatio), p));
	
	return coefficient * load;
}

double Tire::getRollingResistance(double load,double speed)
{
	if (fabs(speed) > 1.0f)
		return rollingResistanceCoefficient * load;
	else
		return 0.0f;
}

double Tire::setSlipRatio(double slipRatio)
{
	this->slipRatio = slipRatio;
}
