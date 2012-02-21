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


bool CylinderHead::canAttachPart(const Part& part) const
{
	const Camshaft* c = dynamic_cast<const Camshaft*>(&part);

	if(c)
		return canAttachCamshaft(*c);
	
	const ExhaustManifold* e = dynamic_cast<const ExhaustManifold*>(&part);

	if(e)
		return canAttachExhaustManifold(*e);
	
	const IntakeManifold* i = dynamic_cast<const IntakeManifold*>(&part);

	if(i)
		return canAttachIntakeManifold(*i);


	return false;
}

bool CylinderHead::canAttachCamshaft(const Camshaft& c) const
{
	if(c.getCylinderCount() != cylinderCount)
		return false;

	if(c.getCamshaftPosition() != camshaftPosition)
		return false;

	return checkCamshaftCount();
}

bool CylinderHead::canAttachExhaustManifold(const ExhaustManifold& c) const
{
	if(c.getCylinderCount() != cylinderCount)
		return false;

	if(c.getCylinderAlignment() != cylinderAlignment)
		return false;

	return checkExhaustManifoldCount();
}

bool CylinderHead::canAttachIntakeManifold(const IntakeManifold& c) const
{
	if(c.getCylinderCount() != cylinderCount)
		return false;

	if(c.getCylinderAlignment() != cylinderAlignment)
		return false;

	return checkIntakeManifoldCount();
}

bool CylinderHead::checkCamshaftCount() const
{
	int count = 0;
	
	for(const Object* i : *this)
	{
		if(dynamic_cast<const Camshaft*>(i))
			count++;
	}
	
	int limit = 1;
	
	if(doubleCam)
		limit *= 2;
	
	if(cylinderAlignment == "V")
		limit *= 2;
	
	if(count < limit)
		return true;
	
	return false;
}

bool CylinderHead::checkExhaustManifoldCount() const
{
	for(const Object* i : *this)
		if(dynamic_cast<const ExhaustManifold*>(i))
			return false;

	return true;	
}


bool CylinderHead::checkIntakeManifoldCount() const
{
	for(const Object* i : *this)
		if(dynamic_cast<const IntakeManifold*>(i))
			return false;

	return true;	
}


CylinderHead* CylinderHead::clone() const
{
	return new CylinderHead(*this);
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

void CylinderHead::save(Json::Value& value)
{
	Part::save(value);

	value["type"] = "cylinderhead";
	value["cylinderCount"] = cylinderCount;
	value["camshaftPosition"] = camshaftPosition;
	value["cylinderAlignment"] = cylinderAlignment;
	value["doubleCam"] = doubleCam;
}

}
