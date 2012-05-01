#include "chassis.hpp"

#include "engine.hpp"
#include "tire.hpp"

namespace Game
{

bool Chassis::canAttachPart(const Part* part) const
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

int Chassis::getAttachmentLimitOfType(const Part* part) const
{
	if(dynamic_cast<const Engine*>(part))
		return 1;
		
	if(dynamic_cast<const Tire*>(part))
		return 4;
		
	return 0;
}

Chassis::Chassis(const Json::Value& value):
	Part(value)
{
	dragCoefficient = value["dragCoefficient"].asDouble();
	length = value["length"].asDouble();
	width = value["width"].asDouble();
	height = value["height"].asDouble();
	wheelbase = value["wheelbase"].asDouble();
	maxEngineVolume = value["maxEngineVolume"].asInt();
	maxEngineCylinderCount = value["maxEngineCylinderCount"].asInt();
}

void Chassis::save(Json::Value& value) const
{
	Part::save(value);

	value["type"] = "chassis";
	value["dragCoefficient"] = dragCoefficient;
	value["length"] = length;
	value["width"] = width;
	value["height"] = height;
	value["wheelbase"] = wheelbase;
	value["maxEngineVolume"] = maxEngineVolume;
	value["maxEngineCylinderCount"] = maxEngineCylinderCount;
}

}
