#include "transmission.hpp"

#include "utils/inifile.hpp"
#include "vehicle.hpp"

const std::string& Transmission::getName() const
{
	return name;
}

int Transmission::getPrice() const
{
	return 0;
}

Transmission::Transmission(IniFile& iniFile):
	PartModel(iniFile)
{
	iniFile.getValue("name",name);
}
