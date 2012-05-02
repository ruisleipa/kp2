#include "injector.hpp"

namespace Game
{
Injector::Injector(const Json::Value& value):
	Part(value)
{

}

void Injector::save(Json::Value& value) const
{
	Part::save(value);

	value["type"] = "injector";
}

}

