#include "clutch.hpp"

#include "utils/inifile.hpp"
#include "vehicle.hpp"

const std::string& Clutch::getName()
{
	return name;
}

int Clutch::getPrice()
{
	return 0;
}

bool Clutch::fitsInVehicle(const Vehicle& vehicle)
{
	return true;
}

Clutch::Clutch(IniFile& iniFile)
{
	iniFile.getValue("name",name);
}
