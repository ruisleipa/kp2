#include "fuelpump.hpp"

#include "utils/inifile.hpp"
#include "vehicle.hpp"

const std::string& FuelPump::getName() const
{
	return name;
}

int FuelPump::getPrice() const
{
	return 0;
}

FuelPump::FuelPump(IniFile& iniFile):
	PartModel(iniFile)
{
	iniFile.getValue("name",name);
}
