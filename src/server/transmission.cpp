#include "transmission.hpp"

#include "utils/inifile.hpp"
#include "vehicle.hpp"

const std::string& Transmission::getName()
{
	return name;
}

int Transmission::getPrice()
{
	return 0;
}

bool Transmission::fitsInVehicle(const Vehicle& vehicle)
{
	return true;
}

Transmission::Transmission(IniFile& iniFile)
{
	iniFile.getValue("name",name);
}
