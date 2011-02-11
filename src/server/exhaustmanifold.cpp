#include "exhaustmanifold.hpp"

#include "utils/inifile.hpp"
#include "vehicle.hpp"

const std::string& ExhaustManifold::getName()
{
	return name;
}

int ExhaustManifold::getPrice()
{
	return 0;
}

bool ExhaustManifold::fitsInVehicle(const Vehicle& vehicle)
{
	return true;
}

ExhaustManifold::ExhaustManifold(IniFile& iniFile)
{
	iniFile.getValue("name",name);
}
