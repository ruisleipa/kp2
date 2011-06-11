#include "race.hpp"

#include "vehiclesimulation.hpp"

Race::Driver::Driver(VehicleSimulation* simulation, int playerId):
	simulation(simulation),
	playerId(playerId)
{

}

void Race::update()
{
	while(first.simulation->getTimeInSeconds() < realTime.getSeconds())
		first.simulation->advance();
		
	while(second.simulation->getTimeInSeconds() < realTime.getSeconds())
		second.simulation->advance();
	
	const float QUARTER_MILE = 402.336;
	const float finishLinePosition = QUARTER_MILE;
	
	float firstPosition = first.simulation->getPosition();
	float secondPosition = second.simulation->getPosition();
	
	if(!winnerChosen)
	{
		if(firstPosition > finishLinePosition || secondPosition > finishLinePosition)
		{
			if(firstPosition > secondPosition)
				winnerId = first.playerId;
			else
				winnerId = second.playerId;
		}
		
		winnerChosen = true;
	}
	
	if(firstPosition > finishLinePosition)
		first.simulation->setBrakeUsage(1.0);
		
	if(secondPosition > finishLinePosition)
		second.simulation->setBrakeUsage(1.0);
}

VehicleSimulation* Race::getSimulationByPlayerId(int playerId)
{
	if(first.playerId == playerId)
		return first.simulation;
	
	if(second.playerId == playerId)
		return second.simulation;
	
	return 0;
}

Race::Race(const Driver& first, const Driver& second):
	first(first),
	second(second),
	winnerId(0),
	winnerChosen(false)
{
	
}
