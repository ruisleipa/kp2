#include "differential.hpp"

namespace Game
{

int Differential::getPrice() const
{
	return 0;
}

Differential::Differential(const Json::Value& value):
	Part(value)
{
	
}

void Differential::save(Json::Value& value)
{
	Part::save(value);

	value["type"] = "differential";
}

}
