#include "vehicle.hpp"

#include <stdexcept>
#include <sstream>

#include "engine.hpp"
#include "tire.hpp"

namespace Game
{

int Vehicle::getPrice() const
{
	return 1000;
}

const std::string& Vehicle::getImageName() const
{
	return imageName;
}

bool Vehicle::canAttachPart(const Part& p) const
{
	const Part* part = &p;

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

Vehicle* Vehicle::clone() const
{
	return new Vehicle(*this);
}

Vehicle::Vehicle(const Json::Value& value):
	Part(value)
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

void Vehicle::save(Json::Value& value)
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
}

}
