#include "differential.hpp"

#include "utils/inifile.hpp"
#include "vehicle.hpp"

const std::string& Differential::getName() const
{
	return name;
}

int Differential::getPrice() const
{
	return 0;
}

bool Differential::fitsInVehicle(const Vehicle& vehicle) const
{
	return true;
}

Differential::Differential(IniFile& iniFile)
{
	iniFile.getValue("name",name);
}
