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

bool Part::canAttachPart(const Part* part) const
{
	return false;
}

int Part::getAttachmentLimitOfType(const Part* part) const
{
	return 0;
}

Part::Part(const Json::Value& value):
	Object(value)
{
	name = value["name"].asString();
	price = value["price"].asInt();
	mass = value["mass"].asDouble();
}

void Part::save(Json::Value& value) const
{
	Object::save(value);

	value["name"] = name;
	value["price"] = price;
	value["mass"] = mass;
}

}
