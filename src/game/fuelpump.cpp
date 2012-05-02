#include "fuelpump.hpp"

namespace Game 
{

FuelPump::FuelPump(const Json::Value& value):
	Part(value)
{

}

void FuelPump::save(Json::Value& value) const
{
	Part::save(value);

	value["type"] = "fuelpump";
}

}

