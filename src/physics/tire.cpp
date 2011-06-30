#include "tire.hpp"
#include "math_tools.hpp"

#include <algorithm>

namespace Physics
{

Tire::Tire(float mass, float radius, float rollingResistanceCoefficient, float frictionCoefficient):
	slipRatio(0),
	radius(radius),
	inertia(0),
	rollingResistanceCoefficient(rollingResistanceCoefficient),
	frictionCoefficient(frictionCoefficient)
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
	float maxForce = load * frictionCoefficient;
	
	float normalizedForce = std::min(slipRatio * 20.0, 1.0);
	
	return normalizedForce * maxForce;
}

double Tire::getRollingResistance(double load,double speed)
{
	return rollingResistanceCoefficient * load * std::min(1.0, speed);
}

double Tire::setSlipRatio(double slipRatio)
{
	this->slipRatio = slipRatio;
}

};
