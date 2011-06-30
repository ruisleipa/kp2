#include "charger.hpp"

#include "utils/inifile.hpp"
#include "vehicle.hpp"

const std::string& Charger::getName() const
{
	return name;
}

float Charger::getMaxSpeed() const
{
	return maxSpeed;
}

float Charger::getAirPerRevolution() const
{
	return airPerRevolution;
}

float Charger::getGearRatio() const
{
	return gearRatio;
}

int Charger::getPrice() const
{
	return airPerRevolution * 10.0 + maxSpeed / 10.0;
}

Charger* Charger::clone() const
{
	return new Charger(*this);
}

Charger::Charger(IniFile& iniFile):
	Part(iniFile)
{
	iniFile.getValue("maxSpeed", maxSpeed);
	iniFile.getValue("airPerRevolution", airPerRevolution);
	iniFile.getValue("gearRatio", gearRatio);
	iniFile.getValue("name", name);
}
