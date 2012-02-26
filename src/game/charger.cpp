#include "charger.hpp"

#include "utils/inifile.hpp"
#include "vehicle.hpp"

namespace Game
{

int Charger::getPrice() const
{
	return airPerRevolution * 10.0 + maxSpeed / 10.0;
}

Charger::Charger(const Json::Value& value):
	Part(value)
{
	maxSpeed = value["maxSpeed"].asUInt();
	airPerRevolution = value["airPerRevolution"].asDouble();
	gearRatio = value["gearRatio"].asDouble();
}

void Charger::save(Json::Value& value)
{
	Part::save(value);

	value["maxSpeed"] = maxSpeed;
	value["airPerRevolution"] = airPerRevolution;
	value["gearRatio"] = gearRatio;
}

}
