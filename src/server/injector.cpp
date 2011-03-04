#include "injector.hpp"

#include "utils/inifile.hpp"
#include "vehicle.hpp"

const std::string& Injector::getName() const
{
	return name;
}

int Injector::getPrice() const
{
	return 0;
}

bool Injector::fitsInVehicle(const Vehicle& vehicle) const
{
	return true;
}

Injector::Injector(IniFile& iniFile)
{
	iniFile.getValue("name",name);
}
