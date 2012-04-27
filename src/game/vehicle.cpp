#include "vehicle.hpp"

#include <stdexcept>
#include <sstream>

#include "engine.hpp"
#include "tire.hpp"

namespace Game
{

int Vehicle::getPrice() const
{
	return Part::getPrice();
}

const std::string& Vehicle::getImageName() const
{
	return imageName;
}

const Container<Part>& Vehicle::getParts() const
{
	return parts;
}

bool Vehicle::canAttachPart(const Part* part) const
{
	const Tire* tire = dynamic_cast<const Tire*>(part);

	if(tire)
		return true;

	const Engine* engine = dynamic_cast<const Engine*>(part);

	if(engine)
	{
		if(engine->getVolume() > maxEngineVolume)
			return false;

		if(engine->getCylinderCount() > maxEngineCylinderCount)
			return false;

		return true;
	}

	return false;
}

void Vehicle::attachPart(Part* part)
{
	parts.add(part);
}

void Vehicle::detachPart(Part* part)
{
	parts.remove(part);
}

Vehicle::Vehicle(const Json::Value& value, ObjectFactory& factory):
	Part(value),
	parts(value["parts"], factory)
{
	info = value["info"].asString();
	imageName = value["imageName"].asString();	
	dragCoefficient = value["dragCoefficient"].asDouble();
	length = value["length"].asDouble();
	width = value["width"].asDouble();
	height = value["height"].asDouble();
	wheelbase = value["wheelbase"].asDouble();
	maxEngineVolume = value["maxEngineVolume"].asInt();
	maxEngineCylinderCount = value["maxEngineCylinderCount"].asInt();
}

void Vehicle::save(Json::Value& value) const
{
	Part::save(value);

	value["type"] = "vehicle";
	value["info"] = info;
	value["imageName"] = imageName;
	value["dragCoefficient"] = dragCoefficient;
	value["length"] = length;
	value["width"] = width;
	value["height"] = height;
	value["wheelbase"] = wheelbase;
	value["maxEngineVolume"] = maxEngineVolume;
	value["maxEngineCylinderCount"] = maxEngineCylinderCount;

	parts.save(value["parts"]);
}

}
