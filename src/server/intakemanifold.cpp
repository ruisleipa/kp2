#include "intakemanifold.hpp"

#include "utils/inifile.hpp"
#include "vehicle.hpp"

const std::string& IntakeManifold::getName() const
{
	return name;
}

int IntakeManifold::getPrice() const
{
	return 0;
}

bool IntakeManifold::fitsInVehicle(const Vehicle& vehicle) const
{
	return true;
}

IntakeManifold::IntakeManifold(IniFile& iniFile)
{
	iniFile.getValue("name",name);
}
