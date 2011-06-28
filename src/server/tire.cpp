#include "tire.hpp"

#include "utils/inifile.hpp"
#include "vehicle.hpp"

float Tire::getFrictionCoefficient() const
{
	return frictionCoefficient;
}

float Tire::getRollingResistanceCoefficient() const
{
	return rollingResistanceCoefficient;
}

float Tire::getRadius() const
{
	return radius;
}

Tire::Tire(IniFile& iniFile):
	PartModel(iniFile)
{
	iniFile.getValue("frictionCoefficient", frictionCoefficient);
	iniFile.getValue("rollingResistanceCoefficient", rollingResistanceCoefficient);
	iniFile.getValue("radius", radius);
}
