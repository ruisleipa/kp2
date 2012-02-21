#include "driver.hpp"

void Driver::updateSimulation(float realTime)
{
	const float QUARTER_MILE = 402.336;
	const float finishLinePosition = QUARTER_MILE;
	const float startLinePosition = 0.0;
	
	while(simulation.getTimeInSeconds() < realTime)
	{
		const float position = simulation.getPosition();
		const float time = simulation.getTimeInSeconds();
		
		if(!started)
		{
			if(position > startLinePosition)
			{
				startTime = time;
				started = true;
			}
		}
		
		if(!finished)
		{
			if(position > finishLinePosition)
			{
				finishTime = time;
				finished = true;
				
				simulation.setThrottleUsage(0);
				simulation.setClutchUsage(1);
				simulation.setIgnition(0);
			}
			
			const float speed = simulation.getSpeed();
			
			if(speed > topSpeed)
				topSpeed = speed;
		}
		
		simulation.advance();
	}
}

void Driver::setControlState(Protocol::ControlState& state)
{
	if(!finished)
	{
		if(state.gearDown)
			simulation.lowerGear();
		
		if(state.gearUp)
			simulation.upperGear();
		
		simulation.setThrottleUsage(state.throttle);
		simulation.setClutchUsage(state.clutch);
		simulation.setIgnition(state.ignition);
	}
}

bool Driver::hasStarted()
{
	return started;
}

float Driver::getStartTime()
{
	return startTime;
}

bool Driver::hasFinished()
{
	return finished;
}

float Driver::getFinishTime()
{
	return finishTime;
}

float Driver::getTopSpeed()
{
	return topSpeed;
}

Vehicle& Driver::getVehicle()
{
	return vehicle;
}

Connection& Driver::getConnection()
{
	return connection;
}

VehicleSimulation& Driver::getSimulation()
{
	return simulation;
}

int Driver::decideTickRate()
{
	return 400;
}

Driver::Driver(Vehicle& vehicle, Connection& connection):
	vehicle(vehicle),
	connection(connection),
	simulation(vehicle, decideTickRate()),
	started(false),
	startTime(0.0),
	finished(false),
	finishTime(0.0),
	topSpeed(0.0)
{

}
