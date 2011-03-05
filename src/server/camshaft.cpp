#include "camshaft.hpp"

#include "utils/inifile.hpp"
#include "vehicle.hpp"
#include "cylinderhead.hpp"

const std::string& Camshaft::getName() const
{
	return name;
}

int Camshaft::getPrice() const
{
	return 0;
}

bool Camshaft::fitsInVehicle(const Vehicle& vehicle) const
{
	
	
	for(size_t i = 0; i < vehicle.getPartCount(); ++i)
	{
		const Part& part = vehicle.getPart(i);
	
		if(part.getType() == "cylinderhead")
		{
			const CylinderHead& cylinderHead = part.getModelImplementation<CylinderHead>();
			
			if(cylinderHead.getCylinderCount() != cylinders)
				return false;
			
			if(cylinderHead.getCamshaftPosition() != camshaftPosition)
				return false;
		}
	}
	
	return true;
}

Camshaft::Camshaft(IniFile& iniFile)
{
	iniFile.getValue("cylinders",cylinders);
	iniFile.getValue("camshaftPosition",camshaftPosition);
	iniFile.getValue("cylinderAlignment",cylinderAlignment);
			
	std::stringstream ss;
	
	//For example:
	//V8 OHC
	//S4 CIH
	//S6 OHV
	
	ss << cylinderAlignment;
	ss << cylinders;
	ss << " ";	
	ss << camshaftPosition;
	ss << " nokka";
	
	name = ss.str();
}
