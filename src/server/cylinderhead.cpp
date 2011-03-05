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

bool CylinderHead::fitsInVehicle(const Vehicle& vehicle) const
{
	const Engine* engine = 0;
		
	for(size_t i = 0; i < vehicle.getPartCount(); ++i)
	{
		const Part& part = vehicle.getPart(i);
		
		if(part.getType() == "engine")
			engine = &(part.getModelImplementation<Engine>());
	}
	
	//no engine, we cannot install a cylinderhead
	if(!engine)
		return false;
	
	int cylinderHeadsNeeded = 1;
	
	if(engine->getCylinderAlignment() == "V")
		cylinderHeadsNeeded = 2;

	int cylinderHeadsInstalled = 0;
		
	for(size_t i = 0; i < vehicle.getPartCount(); ++i)
	{
		if(vehicle.getPart(i).getType() == "cylinderhead")
			cylinderHeadsInstalled++;
	}
	
	//no room for additional cylinderheads
	if(cylinderHeadsInstalled == cylinderHeadsNeeded)
		return false;
		
	if(engine->getCylinderCount() != cylinders)
		return false;
	
	if(engine->getCamshaftPosition() != camshaftPosition)
		return false;

	return true;
}

CylinderHead::CylinderHead(IniFile& iniFile)
{
	iniFile.getValue("cylinders",cylinders);
	iniFile.getValue("camshaftPosition",camshaftPosition);
	iniFile.getValue("doubleCam",doubleCam);
		
	std::stringstream ss;
	
	//For example:
	//V8 DOHC
	//S4 CIH
	//S6 OHV
	
	ss << cylinders;
	ss << "-syl. ";
	
	if(doubleCam)
		ss << "D";
		
	ss << camshaftPosition;
	
	ss << " kansi";
	
	name = ss.str();
}
