#include "fuelintake.hpp"

namespace Game
{

FuelIntake::FuelIntake(const Json::Value& value):
	Part(value)
{

}

void FuelIntake::save(Json::Value& value)
{
	Part::save(value);

	value["type"] = "fuelintake";
}

}

