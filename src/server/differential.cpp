#include "differential.hpp"

#include "utils/inifile.hpp"
#include "vehicle.hpp"

const std::string& Differential::getName()
{
	return name;
}

int Differential::getPrice()
{
	return 0;
}

bool Differential::fitsInVehicle(const Vehicle& vehicle)
{
	return true;
}

Differential::Differential(IniFile& iniFile)
{
	iniFile.getValue("name",name);
}
