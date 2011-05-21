#include "intakemanifold.hpp"

#include "utils/inifile.hpp"
#include "vehicle.hpp"

const std::string& IntakeManifold::getName() const
{
	return name;
}

int IntakeManifold::getPrice() const
{
	return 0;
}

IntakeManifold::IntakeManifold(IniFile& iniFile):
	PartModel(iniFile)
{
	iniFile.getValue("name",name);
}
