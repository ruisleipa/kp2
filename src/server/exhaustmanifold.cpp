#include "exhaustmanifold.hpp"

#include "utils/inifile.hpp"
#include "vehicle.hpp"

const std::string& ExhaustManifold::getName() const
{
	return name;
}

int ExhaustManifold::getPrice() const
{
	return 0;
}

bool ExhaustManifold::fitsInVehicle(const Vehicle& vehicle) const
{
	return true;
}

ExhaustManifold::ExhaustManifold(IniFile& iniFile)
{
	iniFile.getValue("name",name);
}
