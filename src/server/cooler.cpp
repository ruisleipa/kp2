#include "cooler.hpp"

#include "utils/inifile.hpp"
#include "vehicle.hpp"

const std::string& Cooler::getName()
{
	return name;
}

int Cooler::getPrice()
{
	return 0;
}

bool Cooler::fitsInVehicle(const Vehicle& vehicle)
{
	return true;
}

Cooler::Cooler(IniFile& iniFile)
{
	iniFile.getValue("name",name);
}
