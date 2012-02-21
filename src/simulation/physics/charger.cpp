#include "charger.hpp"

#include <algorithm>

namespace Physics
{	

Air Charger::getAir(float maxVolume)
{	
	int speedPercent = speedInRpm / maxSpeed * 100.0;
	
	float volume = speedInRpm * airPerRevolution * efficiencyCurve.getValue(speedPercent);
	
	Air air = getIntake().getAir(volume);
	
	air.compress(maxVolume);
	
	currentPressure = air.getPressure();
	
	return air;
}

float Charger::getPressure()
{
	return currentPressure;
}

void Charger::calculateSpeed(float engineSpeedInRpm)
{
	speedInRpm = std::min(engineSpeedInRpm * gearRatio, maxSpeed);
}

Charger::Charger(Pipe& pipe, float gearRatio, float airPerRevolution, float maxSpeed):
	Pipe(pipe, 0),
	speedInRpm(0),
	gearRatio(gearRatio),
	airPerRevolution(airPerRevolution),
	maxSpeed(maxSpeed),
	currentPressure(0)
{
	efficiencyCurve.addPoint(0, 1.0);
	efficiencyCurve.addPoint(97, 1.0);
	efficiencyCurve.addPoint(99, 0.6);
	efficiencyCurve.addPoint(100, 0);
}

};
