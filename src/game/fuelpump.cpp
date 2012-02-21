#include "fuelpump.hpp"

namespace Game 
{

FuelPump* FuelPump::clone() const
{
	return new FuelPump(*this);
}

FuelPump::FuelPump(const Json::Value& value):
	Part(value)
{

}

void FuelPump::save(Json::Value& value)
{
	Part::save(value);

	value["type"] = "fuelpump";
}

}

