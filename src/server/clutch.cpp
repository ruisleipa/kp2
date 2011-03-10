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

Clutch::Clutch(IniFile& iniFile)
{
	iniFile.getValue("name",name);
}
