#include "vehicle.hpp"

namespace Game
{

const std::string& Vehicle::getName() const
{
	return name;
}

float Vehicle::getMass() const
{
	return 0;
}

int Vehicle::getPrice() const
{
	return price;
}

const std::string& Vehicle::getImageName() const
{
	return imageName;
}

const Container<Part>& Vehicle::getParts() const
{
	return parts;
}

void Vehicle::attachPart(Part* part)
{
	parts.add(part);
}

PartContainer::Parts Vehicle::detachPart(Part* part)
{
	auto detachedParts = parts.getAllAttachedParts(part);

	detachedParts.push_back(part);

	for(Part* p : detachedParts)
		parts.remove(p);

	Json::Value v;

	save(v);

	std::cout << v << std::endl;

	return detachedParts;
}

Vehicle::Vehicle(const Json::Value& value, ObjectFactory& factory):
	Object(value),
	parts(value["parts"], factory)
{
	name = value["name"].asString();
	price = value["price"].asUInt();
	info = value["info"].asString();
	imageName = value["imageName"].asString();	
}

void Vehicle::save(Json::Value& value) const
{
	Object::save(value);

	value["type"] = "vehicle";
	value["name"] = name;
	value["price"] = price;
	value["info"] = info;
	value["imageName"] = imageName;

	parts.save(value["parts"]);
}

}
