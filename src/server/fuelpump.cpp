#include "fuelpump.hpp"

#include "utils/inifile.hpp"
#include "vehicle.hpp"

const std::string& FuelPump::getName() const
{
	return name;
}

int FuelPump::getPrice() const
{
	return 0;
}

bool FuelPump::fitsInVehicle(const Vehicle& vehicle) const
{
	return true;
}

FuelPump::FuelPump(IniFile& iniFile)
{
	iniFile.getValue("name",name);
}
