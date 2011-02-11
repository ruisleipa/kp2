#include "cylinderhead.hpp"

#include "utils/inifile.hpp"
#include "vehicle.hpp"

const std::string& CylinderHead::getName()
{
	return name;
}

int CylinderHead::getPrice()
{
	return 0;
}

bool CylinderHead::fitsInVehicle(const Vehicle& vehicle)
{
	return true;
}

CylinderHead::CylinderHead(IniFile& iniFile)
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
	
	name = ss.str();
}
