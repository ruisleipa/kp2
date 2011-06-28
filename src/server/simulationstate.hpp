#ifndef SERVER_SIMULATIONSTATE_HPP
#define SERVER_SIMULATIONSTATE_HPP

#include <map>
#include <list>
#include <tr1/memory>

#include "protocol/controlstate.hpp"

#include "testrun.hpp"

class SimulationState
{
	public:
		void sendStates();
		
		void setControlState(Connection& connection, Protocol::ControlState& state);
		void updateSimulations();
		
		void startTestRun(Connection& connection);
		
	private:
		std::list<std::tr1::shared_ptr<TestRun> > testRuns;
		std::list<std::tr1::weak_ptr<Driver> > raceSimulations;
		
};

#endif // GAMESTATE_HPP

