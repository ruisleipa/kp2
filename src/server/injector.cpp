#include "injector.hpp"

#include "utils/inifile.hpp"
#include "vehicle.hpp"

const std::string& Injector::getName()
{
	return name;
}

int Injector::getPrice()
{
	return 0;
}

bool Injector::fitsInVehicle(const Vehicle& vehicle)
{
	return true;
}

Injector::Injector(IniFile& iniFile)
{
	iniFile.getValue("name",name);
}
