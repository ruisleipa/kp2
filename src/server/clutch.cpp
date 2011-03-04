#include "clutch.hpp"

#include "utils/inifile.hpp"
#include "vehicle.hpp"

const std::string& Clutch::getName() const
{
	return name;
}

int Clutch::getPrice() const
{
	return 0;
}

bool Clutch::fitsInVehicle(const Vehicle& vehicle) const
{
	return true;
}

Clutch::Clutch(IniFile& iniFile)
{
	iniFile.getValue("name",name);
}
