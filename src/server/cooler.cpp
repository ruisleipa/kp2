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

Cooler* Cooler::clone() const
{
	return new Cooler(*this);
}

Cooler::Cooler(IniFile& iniFile):
	Part(iniFile)
{
	iniFile.getValue("name",name);
}
