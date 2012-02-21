#include "intakemanifold.hpp"

#include <sstream>

#include "cylinderhead.hpp"

namespace Game
{

const std::string& IntakeManifold::getName() const
{
	return name;
}

const std::string& IntakeManifold::getCylinderAlignment() const
{
	return cylinderAlignment;
}

int IntakeManifold::getCylinderCount() const
{
	return cylinderCount;
}

IntakeManifold* IntakeManifold::clone() const
{
	return new IntakeManifold(*this);
}

IntakeManifold::IntakeManifold(const Json::Value& value):
	Part(value)
{
	cylinderCount = value["cylinderCount"].asUInt();
	cylinderAlignment = value["cylinderAlignment"].asString();
	flow = value["flow"].asDouble();
	
	std::stringstream ss;
	
	ss << cylinderAlignment;
	ss << cylinderCount;
	ss << " ";
	
	ss << " -imusarja ";
	ss << flow;
	
	name = ss.str();
}

void IntakeManifold::save(Json::Value& value)
{
	Part::save(value);

	value["type"] = "intakemanifold";
	value["cylinderCount"] = cylinderCount;
	value["cylinderAlignment"] = cylinderAlignment;
	value["flow"] = flow;
}

}
