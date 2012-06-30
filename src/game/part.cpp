#include "part.hpp"

namespace Game
{

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

Part::Part(int price, float mass):
	price(price),
	mass(mass)
{

}

Part::Part(const Json::Value& value):
	PartContainer(value)
{
	price = value["price"].asInt();
	mass = value["mass"].asDouble();
}

void Part::save(Json::Value& value) const
{
	PartContainer::save(value);

	value["price"] = price;
	value["mass"] = mass;
}

}
