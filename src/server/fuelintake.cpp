#include "fuelintake.hpp"

#include "utils/inifile.hpp"
#include "vehicle.hpp"

const std::string& FuelIntake::getName() const
{
	return name;
}

int FuelIntake::getPrice() const
{
	return 0;
}

bool FuelIntake::fitsInVehicle(const Vehicle& vehicle) const
{
	return true;
}

FuelIntake::FuelIntake(IniFile& iniFile)
{
	iniFile.getValue("name",name);
}
