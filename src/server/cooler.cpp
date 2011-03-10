#include "cooler.hpp"

#include "utils/inifile.hpp"
#include "vehicle.hpp"

const std::string& Cooler::getName() const
{
	return name;
}

int Cooler::getPrice() const
{
	return 0;
}

Cooler::Cooler(IniFile& iniFile)
{
	iniFile.getValue("name",name);
}
