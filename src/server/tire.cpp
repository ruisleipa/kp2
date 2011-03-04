#include "tire.hpp"

#include "utils/inifile.hpp"
#include "vehicle.hpp"

const std::string& Tire::getName() const
{
	return name;
}

int Tire::getPrice() const
{
	return 0;
}

bool Tire::fitsInVehicle(const Vehicle& vehicle) const
{
	return true;
}

Tire::Tire(IniFile& iniFile)
{
	iniFile.getValue("name",name);
}
