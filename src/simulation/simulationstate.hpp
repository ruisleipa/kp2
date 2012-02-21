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
		void updateSimulations();
		
		void startTestRun(Connection& connection);
		
		void setControlState(Connection& connection, Protocol::ControlState& state);
		void quitSimulation(Connection& connection);
		
	private:
		void deleteUnusedTestRuns();
		
		std::list<std::tr1::shared_ptr<TestRun> > testRuns;
		std::map<Connection*, std::tr1::shared_ptr<Driver> > drivers;
		
};

#endif // GAMESTATE_HPP

