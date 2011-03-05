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
	for(size_t i = 0; i < vehicle.getPartCount(); ++i)
	{
		const Part& part = vehicle.getPart(i);
	
		if(part.getType() == "engine")
		{
			const Engine& engine = part.getModelImplementation<Engine>();
			
			if(engine.getCylinderCount() != cylinders)
				return false;
			
			if(engine.getCamshaftPosition() != camshaftPosition)
				return false;
				
			if(engine.getCylinderAlignment() != cylinderAlignment)
				return false;
		}
	}
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
