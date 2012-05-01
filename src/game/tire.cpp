#include "tire.hpp"

#include <sstream>

namespace Game
{

const std::string& Tire::getName() const
{
	return name;
}

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

	std::stringstream name;

	name << radius * 2 << "\"";

	this->name = name.str();
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

