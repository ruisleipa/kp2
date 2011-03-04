#include "engine.hpp"

#include "utils/inifile.hpp"
#include "vehicle.hpp"

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
	return cylinders;
}

bool Engine::fitsInVehicle(const Vehicle& vehicle) const
{
	return true;
}

Engine::Engine(IniFile& iniFile)
{
	iniFile.getValue("cylinders",cylinders);
	iniFile.getValue("camshaftPosition",camshaftPosition);
	iniFile.getValue("cylinderAlignment",cylinderAlignment);
	
	iniFile.getValue("compression",compression);
	iniFile.getValue("volume",volume);
	
	volume /= 1000.0;
		
	std::stringstream ss;
	
	//For example:
	//1.0L S4 OHV 
	//3.0L S6 DOHC
	//2.6L V6 OHC
	
	ss << volume;
	ss << "L ";
	
	ss << cylinderAlignment;
	ss << cylinders;
	ss << " ";
	
	ss << camshaftPosition;
	
	name = ss.str();
}
