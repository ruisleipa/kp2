#include "simulationstate.hpp"

#include "player.hpp"

void SimulationState::sendStates()
{
	std::list<std::tr1::shared_ptr<TestRun> >::iterator i;
	
	for(i = testRuns.begin(); i != testRuns.end(); ++i)
	{
		(*i)->sendState();
	}
}

void SimulationState::setControlState(Connection& connection, Protocol::ControlState& state)
{
	Player& player = connection.getPlayer();
	
	std::tr1::shared_ptr<Driver> driver = player.getDriver();
	
	if(driver)
	{
		driver->setControlState(state);
	}
}

void SimulationState::updateSimulations()
{
	std::list<std::tr1::shared_ptr<TestRun> >::iterator i;
	
	for(i = testRuns.begin(); i != testRuns.end(); ++i)
	{
		(*i)->update();
	}
}

void SimulationState::startTestRun(Connection& connection)
{
	Player& player = connection.getPlayer();
	
	Vehicle& vehicle = player.getVehicle(player.getActiveVehicleId());
	
	std::tr1::shared_ptr<Driver> driver(new Driver(vehicle, connection));
	
	player.setDriver(driver);
	
	testRuns.push_back(std::tr1::shared_ptr<TestRun>(new TestRun(driver)));
}
