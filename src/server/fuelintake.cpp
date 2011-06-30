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

FuelIntake* FuelIntake::clone() const
{
	return new FuelIntake(*this);
}

FuelIntake::FuelIntake(IniFile& iniFile):
	Part(iniFile)
{
	iniFile.getValue("name",name);
}
