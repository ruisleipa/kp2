#include "clutch.hpp"

namespace Game
{

int Clutch::getPrice() const
{
	return 0;
}

Clutch::Clutch(const Json::Value& value):
	Part(value)
{

}

void Clutch::save(Json::Value& value)
{
	Part::save(value);

	value["type"] = "clutch";
}

}
