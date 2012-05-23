#include "engine.hpp"

#include <sstream>

#include "cylinderhead.hpp"

namespace Game
{

const std::string& Engine::getName() const
{
	return name;
}

int Engine::getPrice() const
{
	return 0;
}

const std::string& Engine::getCamshaftPosition() const
{
	return camshaftPosition;
}

const std::string& Engine::getCylinderAlignment() const
{
	return cylinderAlignment;
}
	
int Engine::getCylinderCount() const
{
	return cylinderCount;
}

float Engine::getVolume() const
{
	return volume;
}

const Curve& Engine::getTorqueCurve() const
{
	return torqueCurve;
}

int Engine::getIdleSpeed() const
{
	return 1000;
}

int Engine::getSpeedLimit() const
{
	return 8000;
}

bool Engine::canAttachPart(const Part* part) const
{
	const CylinderHead* c = dynamic_cast<const CylinderHead*>(part);

	if(c)
		return canAttachCylinderHead(*c);

	return false;
}

int Engine::getAttachmentLimitOfType(const Part* part) const
{
	if(dynamic_cast<const CylinderHead*>(part))
		return 1;

	return 0;
}

bool Engine::canAttachCylinderHead(const CylinderHead& c) const
{
	if(c.getCylinderCount() != cylinderCount)
		return false;

	if(c.getCamshaftPosition() != camshaftPosition)
		return false;

	if(c.getCylinderAlignment() != cylinderAlignment)
		return false;

	return true;
}

Engine::Engine(const Json::Value& value):
	Part(value)
{
	cylinderCount = value["cylinderCount"].asUInt();
	camshaftPosition = value["camshaftPosition"].asString();
	cylinderAlignment = value["cylinderAlignment"].asString();
	compression = value["compression"].asDouble();
	volume = value["volume"].asUInt();
	torqueCurve = Curve(value["torqueCurve"]);

		
	std::stringstream ss;
	
	//For example:
	//1.0L S4 OHV 
	//3.0L S6 DOHC
	//2.6L V6 OHC
	
	ss << volume / 1000.0;
	ss << "L ";
	
	ss << cylinderAlignment;
	ss << cylinderCount;
	ss << " ";
	
	ss << camshaftPosition;
	
	name = ss.str();
}

void Engine::save(Json::Value& value) const
{
	Part::save(value);

	value["type"] = "engine";
	value["cylinderCount"] = cylinderCount;
	value["camshaftPosition"] = camshaftPosition;
	value["cylinderAlignment"] = cylinderAlignment;
	value["compression"] = compression;
	value["volume"] = volume;

	torqueCurve.save(value["torqueCurve"]);
}

}
