#include "simulationstate.hpp"

#include "player.hpp"

void SimulationState::sendStates()
{
	deleteUnusedTestRuns();
	
	std::list<std::tr1::shared_ptr<TestRun> >::iterator i;
	
	for(i = testRuns.begin(); i != testRuns.end(); ++i)
		(*i)->sendState();
}

void SimulationState::updateSimulations()
{
	deleteUnusedTestRuns();
	
	std::list<std::tr1::shared_ptr<TestRun> >::iterator i;
	
	for(i = testRuns.begin(); i != testRuns.end(); ++i)
		(*i)->update();
}

void SimulationState::startTestRun(Connection& connection)
{
	Player& player = connection.getPlayer();
	
	Vehicle& vehicle = player.getVehicle(player.getActiveVehicleId());
	
	std::tr1::shared_ptr<Driver> driver(new Driver(vehicle, connection));
	
	drivers[&connection] = driver;
	
	testRuns.push_back(std::tr1::shared_ptr<TestRun>(new TestRun(driver)));
}

void SimulationState::setControlState(Connection& connection, Protocol::ControlState& state)
{
	drivers[&connection]->setControlState(state);
}

void SimulationState::quitSimulation(Connection& connection)
{
	drivers.erase(&connection);
}

void SimulationState::deleteUnusedTestRuns()
{
	std::list<std::tr1::shared_ptr<TestRun> >::iterator i;
	
	for(i = testRuns.begin(); i != testRuns.end(); ++i)
		if((*i)->canDelete())
			i = testRuns.erase(i);
}
