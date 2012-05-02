#include "cooler.hpp"

namespace Game
{

int Cooler::getPrice() const
{
	return 0;
}

Cooler::Cooler(const Json::Value& value):
	Part(value)
{
	
}

void Cooler::save(Json::Value& value) const
{
	Part::save(value);

	value["type"] = "cooler";
}

}
