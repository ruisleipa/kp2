#include "fuelpump.hpp"

#include "utils/inifile.hpp"
#include "vehicle.hpp"

const std::string& FuelPump::getName()
{
	return name;
}

int FuelPump::getPrice()
{
	return 0;
}

bool FuelPump::fitsInVehicle(const Vehicle& vehicle)
{
	return true;
}

FuelPump::FuelPump(IniFile& iniFile)
{
	iniFile.getValue("name",name);
}
