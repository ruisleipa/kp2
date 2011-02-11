#include "intakemanifold.hpp"

#include "utils/inifile.hpp"
#include "vehicle.hpp"

const std::string& IntakeManifold::getName()
{
	return name;
}

int IntakeManifold::getPrice()
{
	return 0;
}

bool IntakeManifold::fitsInVehicle(const Vehicle& vehicle)
{
	return true;
}

IntakeManifold::IntakeManifold(IniFile& iniFile)
{
	iniFile.getValue("name",name);
}
