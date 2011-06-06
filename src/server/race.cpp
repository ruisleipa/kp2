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
	
	if(!winnerChosen)
	{
		const float finishLinePosition = 402.336;
		
		float firstPosition = first.simulation->getPosition();
		float secondPosition = second.simulation->getPosition();
		
		if(firstPosition > finishLinePosition || secondPosition > finishLinePosition)
		{
			if(firstPosition > secondPosition)
				winnerId = first.playerId;
			else
				winnerId = second.playerId;
		}
		
		winnerChosen = true;
	}
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
