#include "transmission.hpp"

namespace Game
{

std::vector<float> Transmission::getGearRatios() const
{
	return gears;
}

int Transmission::getNeutralGearIndex() const
{
	return neutralGear;
}

Transmission::Transmission(const Json::Value& value):
	Part(value)
{
	neutralGear = 0;	

	for(auto i : value["ratios"])
		gears.push_back(i.asDouble());
}

void Transmission::save(Json::Value& value) const
{
	Part::save(value);	

	for(float i : gears)
		value["ratios"].append(i);
}

}

