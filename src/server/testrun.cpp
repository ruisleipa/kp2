#include "testrun.hpp"

#include "result.hpp"

#include "protocol/protocol.hpp"

void TestRun::sendState()
{
	shared_ptr<Driver> driver = this->driver.lock();
	
	VehicleSimulation& simulation = driver->getSimulation();
	
	Protocol::SimulationVehicleState state;
	
	state.id = 0;
	state.time = simulation.getTimeInSeconds();
	state.position = simulation.getPosition();
	state.speed = simulation.getSpeed();
	state.engineSpeedInRpm = simulation.getEngineSpeedInRpm();
	state.boostPressure = simulation.getBoostPressure();
	
	Packet packet;
	packet.setType(Protocol::DATA_SIMULATION_VEHICLE_STATE);
	packet << state;
	
	Connection& connection = driver->getConnection();
	connection.sendPacket(packet);
}

void TestRun::update()
{
	shared_ptr<Driver> driver = this->driver.lock();
	
	driver->updateSimulation(realTime.getSeconds());
	
	if(driver->hasFinished())
	{
		Protocol::SimulationVehicleResult result;
		
		result.reactionTime = 0;
		result.elapsedTime = driver->getFinishTime() - driver->getStartTime();
		result.totalTime = result.elapsedTime + result.reactionTime;
		result.topSpeed = driver->getTopSpeed();
		
		Connection& connection = driver->getConnection();
		
		Packet packet;
		packet.setType(Protocol::DATA_SIMULATION_VEHICLE_RESULT);
		packet << result;
		
		connection.sendPacket(packet);
	}
}

bool TestRun::canDelete()
{
	if(driver.lock())
		return false;
	
	return true;
}

TestRun::TestRun(std::tr1::weak_ptr<Driver> driver):
	driver(driver)
{
	sendStart();
	sendVehicleData();
}

void TestRun::sendStart()
{
	shared_ptr<Driver> driver = this->driver.lock();
	
	Connection& connection = driver->getConnection();
	
	Packet packet;
	packet.setType(Protocol::DATA_SIMULATION_START);
	
	connection.sendPacket(packet);
}

void TestRun::sendVehicleData()
{
	shared_ptr<Driver> driver = this->driver.lock();
	
	Connection& connection = driver->getConnection();
	
	Protocol::SimulationVehicleData vehicleData;
	
	vehicleData.id = 0;
	vehicleData.imageName = driver->getVehicle().getModel().getImageName();
	vehicleData.width = driver->getVehicle().getModel().getWidth();
	
	Packet packet;
	packet.setType(Protocol::DATA_SIMULATION_VEHICLE_DATA);
	packet << vehicleData;
	
	connection.sendPacket(packet);
}
