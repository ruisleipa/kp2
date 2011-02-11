#include "tire.hpp"

#include "utils/inifile.hpp"
#include "vehicle.hpp"

const std::string& Tire::getName()
{
	return name;
}

int Tire::getPrice()
{
	return 0;
}

bool Tire::fitsInVehicle(const Vehicle& vehicle)
{
	return true;
}

Tire::Tire(IniFile& iniFile)
{
	iniFile.getValue("name",name);
}
