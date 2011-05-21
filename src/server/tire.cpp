#include "tire.hpp"

#include "utils/inifile.hpp"
#include "vehicle.hpp"

const std::string& Tire::getName() const
{
	return name;
}

int Tire::getPrice() const
{
	return 0;
}

Tire::Tire(IniFile& iniFile):
	PartModel(iniFile)
{
	iniFile.getValue("name",name);
}
