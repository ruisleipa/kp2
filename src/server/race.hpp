#ifndef SERVER_RACE_HPP
#define SERVER_RACE_HPP

#include "utils/timer.hpp"

class VehicleSimulation;

class Race
{
	public:
		class Driver
		{
			public:
				VehicleSimulation* simulation;
				int playerId;
				
				Driver(VehicleSimulation* simulation, int playerId);
		};
		
		void update();
		VehicleSimulation* getSimulationByPlayerId(int playerId);
		
		Race(const Driver& first, const Driver& second);
		
	private:
		Driver first;
		Driver second;
		
		int winnerId;
		bool winnerChosen;
		
		Timer realTime;
};

#endif

