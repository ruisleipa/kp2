#include "differential.hpp"

#include "utils/inifile.hpp"
#include "vehicle.hpp"

const std::string& Differential::getName() const
{
	return name;
}

int Differential::getPrice() const
{
	return 0;
}

Differential::Differential(IniFile& iniFile):
	PartModel(iniFile)
{
	iniFile.getValue("name",name);
}
