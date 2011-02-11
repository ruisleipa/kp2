#include "fuelintake.hpp"

#include "utils/inifile.hpp"
#include "vehicle.hpp"

const std::string& FuelIntake::getName()
{
	return name;
}

int FuelIntake::getPrice()
{
	return 0;
}

bool FuelIntake::fitsInVehicle(const Vehicle& vehicle)
{
	return true;
}

FuelIntake::FuelIntake(IniFile& iniFile)
{
	iniFile.getValue("name",name);
}
