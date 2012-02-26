#include "part.hpp"

#include "upgrade.hpp"

#include <stdexcept>

namespace Game
{

const std::string& Part::getName() const
{
	return name;
}

int Part::getPrice() const
{
	return price;
}

float Part::getMass() const
{
	return mass;
}

Part::Part(const Json::Value& value):
	Object(value)
{
	name = value["name"].asString();
	price = value["price"].asInt();
	mass = value["mass"].asDouble();
}

void Part::save(Json::Value& value)
{
	Object::save(value);

	value["name"] = name;
	value["price"] = price;
	value["mass"] = mass;
}

}
