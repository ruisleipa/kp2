#include "chassis.hpp"

namespace Game
{

float Chassis::getDragCoefficient() const
{
	return dragCoefficient;
}

const Chassis::Dimensions& Chassis::getDimensions() const
{
	return dimensions;
}

const Chassis::EngineConstraints& Chassis::getEngineConstraints() const
{
	return engineConstraints;
}

void Chassis::applyPropertiesOf(const Chassis& chassis)
{
	dragCoefficient = chassis.getDragCoefficient();
	dimensions = chassis.getDimensions();
	engineConstraints = chassis.getEngineConstraints();
}

Chassis::Chassis(float mass, float dragCoefficient, const Dimensions& dimensions, const EngineConstraints& engineConstraints):
	Part(0, mass),
	dragCoefficient(dragCoefficient),
	dimensions(dimensions),
	engineConstraints(engineConstraints)
{
	registerSlot("cylinderBlock", &cylinderBlock);
}

Chassis::Chassis(const Json::Value& value):
	Part(value),
	cylinderBlock(value["cylinderBlock"])
{
	dragCoefficient = value["dragCoefficient"].asDouble();
	dimensions.length = value["dimensions"]["length"].asDouble();
	dimensions.width = value["dimensions"]["width"].asDouble();
	dimensions.height = value["dimensions"]["height"].asDouble();
	dimensions.wheelbase = value["dimensions"]["wheelbase"].asDouble();
	dimensions.axleTrack = value["dimensions"]["axleTrack"].asDouble();
	engineConstraints.maxVolume = value["engineConstraints"]["maxEngineVolume"].asInt();
	engineConstraints.maxCylinderCount = value["engineConstraints"]["maxEngineCylinderCount"].asInt();

	registerSlot("cylinderBlock", &cylinderBlock);
}

void Chassis::save(Json::Value& value) const
{
	Part::save(value);

	value["type"] = "Chassis";
	value["dragCoefficient"] = dragCoefficient;
	value["dimensions"]["length"] = dimensions.length;
	value["dimensions"]["width"] = dimensions.width;
	value["dimensions"]["height"] = dimensions.height;
	value["dimensions"]["wheelbase"] = dimensions.wheelbase;
	value["dimensions"]["axleTrack"] = dimensions.axleTrack;
	value["engineConstraints"]["maxEngineVolume"] = engineConstraints.maxVolume;
	value["engineConstraints"]["maxEngineCylinderCount"] = engineConstraints.maxCylinderCount;

	cylinderBlock.save(value["cylinderBlock"]);
}

}
