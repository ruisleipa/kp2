#include "tire.hpp"

namespace Game
{

float Tire::getFrictionCoefficient() const
{
	return frictionCoefficient;
}

float Tire::getRollingResistanceCoefficient() const
{
	return rollingResistanceCoefficient;
}

float Tire::getRadius() const
{
	return radius;
}

Tire::Tire(const Json::Value& value):
	Part(value)
{
	frictionCoefficient = value["frictionCoefficient"].asDouble();
	rollingResistanceCoefficient = value["rollingResistanceCoefficient"].asDouble();
	radius = value["radius"].asDouble();
}

void Tire::save(Json::Value& value) const
{
	Part::save(value);

	value["type"] = "tire";
	value["frictionCoefficient"] = frictionCoefficient;
	value["rollingResistanceCoefficient"] = rollingResistanceCoefficient;
	value["radius"] = radius;
}

}

