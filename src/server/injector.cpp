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

Injector::Injector(IniFile& iniFile):
	PartModel(iniFile)
{
	iniFile.getValue("name",name);
}
