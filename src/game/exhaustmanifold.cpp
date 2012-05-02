#include "exhaustmanifold.hpp"

#include "exhaustpipe.hpp"

namespace Game
{

float ExhaustManifold::getFlow() const
{
	return flow;
}

const std::string& ExhaustManifold::getCylinderAlignment() const
{
	return cylinderAlignment;
}

int ExhaustManifold::getCylinderCount() const
{
	return cylinderCount;
}

ExhaustManifold::ExhaustManifold(const Json::Value& value):
	Part(value)
{
	cylinderCount = value["cylinderCount"].asUInt();
	cylinderAlignment = value["cylinderAlignment"].asString();
	flow = value["flow"].asDouble();
}

void ExhaustManifold::save(Json::Value& value) const
{
	Part::save(value);

	value["type"] = "exhaustmanifold";
	value["cylinderCount"] = cylinderCount;
	value["cylinderAlignment"] = cylinderAlignment;
	value["flow"] = flow;
}

}
