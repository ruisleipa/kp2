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


ExhaustManifold* ExhaustManifold::clone() const
{
	return new ExhaustManifold(*this);
}


bool ExhaustManifold::canAttachPart(const Part& part) const
{	
	for(Object* p : *this)
		if(dynamic_cast<const ExhaustPipe*>(p))
			return false;	
	
	const ExhaustPipe* c = dynamic_cast<const ExhaustPipe*>(&part);
	
	if(c)
		return true;

	return false;
}

ExhaustManifold::ExhaustManifold(const Json::Value& value):
	Part(value)
{
	cylinderCount = value["cylinderCount"].asUInt();
	cylinderAlignment = value["cylinderAlignment"].asString();
	flow = value["flow"].asDouble();
}

void ExhaustManifold::save(Json::Value& value)
{
	Part::save(value);

	value["type"] = "exhaustmanifold";
	value["cylinderCount"] = cylinderCount;
	value["cylinderAlignment"] = cylinderAlignment;
	value["flow"] = flow;
}

}
