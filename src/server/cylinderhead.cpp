#include "cylinderhead.hpp"

#include "utils/inifile.hpp"
#include "vehicle.hpp"
#include "engine.hpp"

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
	return cylinders;
}

bool CylinderHead::isDoubleCam() const
{
	return doubleCam;
}

void CylinderHead::checkPrerequisiteParts(const Vehicle& vehicle) const
{
	bool engineInstalled = false;
		
	for(size_t i = 0; i < vehicle.getPartCount(); ++i)
	{
		const Part& part = vehicle.getPart(i);
		
		if(part.getType() == "engine")
		{
			engineInstalled = true;
		
			const Engine& engine = dynamic_cast<const Engine&>(part);
			
			if(engine.getCylinderCount() != cylinders)
				throw PartDoesNotFitException("CYLINDERHEAD_CYLINDERCOUNT_DOES_NOT_MATCH");
			
			if(engine.getCamshaftPosition() != camshaftPosition)
				throw PartDoesNotFitException("CYLINDERHEAD_CAMSHAFTPOSITION_DOES_NOT_MATCH");
				
			if(engine.getCylinderAlignment() != cylinderAlignment)
				throw PartDoesNotFitException("CYLINDERHEAD_CYLINDERALIGNMENT_DOES_NOT_MATCH");
		}
	}
	
	if(engineInstalled == false)
		throw PartDoesNotFitException("NO_ENGINE_FOR_CYLINDERHEAD");
}

void CylinderHead::checkForExtraPartsOfThisType(const Vehicle& vehicle) const
{
	int cylinderHeadsNeeded = 0;

	for(size_t i = 0; i < vehicle.getPartCount(); ++i)
	{
		const Part& part = vehicle.getPart(i);
		
		if(part.getType() == "engine")
		{
			cylinderHeadsNeeded = 1;
		}		
	}
	
	int cylinderHeadsInstalled = 0;
		
	for(size_t i = 0; i < vehicle.getPartCount(); ++i)
	{
		if(vehicle.getPart(i).getType() == "cylinderhead")
			cylinderHeadsInstalled++;
	}

	if(cylinderHeadsNeeded == cylinderHeadsInstalled)
		throw PartDoesNotFitException("NO_ROOM_FOR_EXTRA_CYLINDERHEAD");
}

CylinderHead* CylinderHead::clone() const
{
	return new CylinderHead(*this);
}

CylinderHead::CylinderHead(IniFile& iniFile):
	Part(iniFile)
{
	iniFile.getValue("cylinders",cylinders);
	iniFile.getValue("camshaftPosition",camshaftPosition);
	iniFile.getValue("cylinderAlignment",cylinderAlignment);
	iniFile.getValue("doubleCam",doubleCam);
		
	std::stringstream ss;
	
	//For example:
	//V8 DOHC
	//S4 CIH
	//S6 OHV
	
	ss << cylinderAlignment;
	ss << cylinders;
	ss << " ";
	
	if(doubleCam)
		ss << "D";
		
	ss << camshaftPosition;
	
	ss << " -kansi";
	
	name = ss.str();
}
