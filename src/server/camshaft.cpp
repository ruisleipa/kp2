#include "camshaft.hpp"

#include "utils/inifile.hpp"
#include "vehicle.hpp"

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
