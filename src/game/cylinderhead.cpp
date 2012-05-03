#include "cylinderhead.hpp"

#include "utils/inifile.hpp"
#include "camshaft.hpp"
#include "exhaustmanifold.hpp"
#include "intakemanifold.hpp"

namespace Game
{

const std::string& CylinderHead::getName() const
{
	return name;
}

int CylinderHead::getPrice() const
{
	return 0;
}

const std::string& CylinderHead::getCamshaftPosition() const
{
	return camshaftPosition;
}

const std::string& CylinderHead::getCylinderAlignment() const
{
	return cylinderAlignment;
}

int CylinderHead::getCylinderCount() const
{
	return cylinderCount;
}

bool CylinderHead::isDoubleCam() const
{
	return doubleCam;
}

bool CylinderHead::canAttachPart(const Part* part) const
{
	const IntakeManifold* intakeManifold = dynamic_cast<const IntakeManifold*>(part);

	if(intakeManifold)
	{
		if(intakeManifold->getCylinderCount() != cylinderCount)
			return false;

		if(intakeManifold->getCylinderAlignment() != cylinderAlignment)
			return false;

		return true;
	}

	const ExhaustManifold* exhaustManifold = dynamic_cast<const ExhaustManifold*>(part);

	if(exhaustManifold)
	{
		if(exhaustManifold->getCylinderCount() != cylinderCount)
			return false;

		if(exhaustManifold->getCylinderAlignment() != cylinderAlignment)
			return false;

		return true;
	}

	const Camshaft* camshaft = dynamic_cast<const Camshaft*>(part);

	if(camshaft)
	{
		if(camshaft->getCylinderCount() != cylinderCount)
			return false;

		if(camshaft->getCamshaftPosition() != camshaftPosition)
			return false;

		return true;
	}

	return false;
}

int CylinderHead::getAttachmentLimitOfType(const Part* part) const
{
	if(dynamic_cast<const IntakeManifold*>(part))
		return 1;

	if(dynamic_cast<const ExhaustManifold*>(part))
		return 1;

	if(dynamic_cast<const Camshaft*>(part))
		return 1;

	return 0;
}

CylinderHead::CylinderHead(const Json::Value& value):
	Part(value)
{
	cylinderCount = value["cylinderCount"].asUInt();
	camshaftPosition = value["camshaftPosition"].asString();
	cylinderAlignment = value["cylinderAlignment"].asString();
	doubleCam = value["doubleCam"].asBool();

	std::stringstream ss;
	
	ss << cylinderAlignment;
	ss << cylinderCount;
	ss << " ";
	
	if(doubleCam)
		ss << "D";
		
	ss << camshaftPosition;
	
	ss << " -kansi";
	
	name = ss.str();
}

void CylinderHead::save(Json::Value& value) const
{
	Part::save(value);

	value["type"] = "cylinderhead";
	value["cylinderCount"] = cylinderCount;
	value["camshaftPosition"] = camshaftPosition;
	value["cylinderAlignment"] = cylinderAlignment;
	value["doubleCam"] = doubleCam;
}

}
