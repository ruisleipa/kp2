#include "transmission.hpp"

namespace Game
{

float Transmission::getEfficiency() const
{
	return efficiency;
}

std::vector<float> Transmission::getGearRatios() const
{
	return gears;
}

Transmission::Transmission(const Json::Value& value):
	Part(value)
{
	efficiency = value["efficiency"].asDouble();

	for(auto i : value["ratios"])
		gears.push_back(i.asDouble());
}

void Transmission::save(Json::Value& value) const
{
	Part::save(value);

	value["efficiency"] = efficiency;

	for(float i : gears)
		value["ratios"].append(i);
}

}

