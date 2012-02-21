#include "dynamometer.hpp"


void Dynamometer::run()
{
	int nextSpeed = 0;
	const int speedStep = 25;
	
	float idleSpeed = 1000;
	
	float time = simulation.getTimeInSeconds();
	
	while(simulation.getTimeInSeconds() < 60.0)
	{
		simulation.advance();
	
		if(simulation.getEngineSpeedInRpm() < idleSpeed)
			simulation.setIgnition(true);
		else
			simulation.setIgnition(false);
			
		if(simulation.getEngineSpeedInRpm() >= idleSpeed)
			simulation.setThrottleUsage(1.0);
			
		if(simulation.getEngineSpeedInRpm() >= nextSpeed && simulation.getEngineSpeedInRpm() > 1000)
		{
			float speed = simulation.getEngineSpeedInRpm();
			
			float torque = simulation.getEngineTorque();
			
			torqueData.addPoint(speed, torque);
			powerData.addPoint(speed, torque * (simulation.getEngineSpeedInRpm() * RPM_TO_RADS) / 1000.0);
			intakeData.addPoint(speed, 0);
			exhaustData.addPoint(speed, 0);
			boostData.addPoint(speed, simulation.getBoostPressure());
			intakeTemperatureData.addPoint(speed, 0);
			
			nextSpeed += speedStep;
		}
	}
}

const Curve& Dynamometer::getTorqueData()
{
	return torqueData;
}

const Curve& Dynamometer::getPowerData()
{
	return powerData;
}

const Curve& Dynamometer::getIntakeData()
{
	return intakeData;
}

const Curve& Dynamometer::getExhaustData()
{
	return exhaustData;
}

const Curve& Dynamometer::getBoostData()
{
	return boostData;
}

const Curve& Dynamometer::getIntakeTemperatureData()
{
	return intakeTemperatureData;
}

Dynamometer::Dynamometer(Vehicle& vehicle):
	simulation(vehicle)
{

}

