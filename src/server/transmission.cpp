#include "transmission.hpp"

#include "utils/inifile.hpp"
#include "vehicle.hpp"

const std::string& Transmission::getName() const
{
	return name;
}

int Transmission::getPrice() const
{
	return 0;
}

bool Transmission::fitsInVehicle(const Vehicle& vehicle) const
{
	return true;
}

Transmission::Transmission(IniFile& iniFile)
{
	iniFile.getValue("name",name);
}
