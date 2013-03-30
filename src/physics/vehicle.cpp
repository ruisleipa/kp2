#include "vehicle.hpp"

#include <cmath>
#include <iostream>

namespace Physics
{

void Vehicle::advanceSimulation()
{
	const double PI = 3.14159265;
	const double RADS_TO_RPM = 60.0f / (2.0f * PI);
	const Seconds dt = 0.1d;

	state.time += dt;

	if(state.engineSpeed * RADS_TO_RPM > 1000)
		starter.setRunning(false);

	NewtonMeters engineTorque = 0.0d;

	engineTorque += engine.getTorque();

	state.engineTorque = engineTorque;
	state.enginePower = state.engineTorque * state.engineSpeed;

	engineTorque += flywheel.getTorque();
	engineTorque += starter.getTorque(state.engineSpeed);

	double engineInertia = 0.0d;

	engineInertia += starter.getInertia();
	engineInertia += flywheel.getInertia();

	state.engineSpeed += engineTorque / engineInertia * dt;
}

const Vehicle::State& Vehicle::getState()
{
	return state;
}

Vehicle::Vehicle(const Game::Vehicle& vehicle):
	vehicle(vehicle),
	starter(),
	flywheel(),
	engine(findNumberOfCylinders(), findCylinderGeometry())
{
	starter.setRunning(true);

	state.enginePower = 0.0;
	state.engineSpeed = 0.0;
	state.engineTorque = 0.0;
	state.time = 0.0;
}

int Vehicle::findNumberOfCylinders()
{
	return getCylinderBlock().getCylinderCount();
}

Engine::CylinderGeometry Vehicle::findCylinderGeometry()
{
	Engine::CylinderGeometry geometry;

	geometry.bore = getCylinderBlock().getBore() / 1000.0;
	geometry.stroke = getCrankshaft().getStroke() / 1000.0;

	const double PI = 3.14159265;

	geometry.compressionVolume = PI * std::pow(geometry.bore / 2.0, 2.0) * getCylinderHead().getChamberHeight() / 1000.0;

	return geometry;
}

Game::Chassis& Vehicle::getChassis()
{
	Game::Chassis* chassis = vehicle.getChassisSlot().getPart();

	if(!chassis)
		throw InvalidVehicleException();

	return *chassis;
}

Game::CylinderBlock& Vehicle::getCylinderBlock()
{
	Game::CylinderBlock* cylinderBlock = getChassis().getCylinderBlockSlot().getPart();

	if(!cylinderBlock)
		throw InvalidVehicleException();

	return *cylinderBlock;
}

Game::Crankshaft& Vehicle::getCrankshaft()
{
	Game::Crankshaft* crankshaft = getCylinderBlock().getCrankshaftSlot().getPart();

	if(!crankshaft)
		throw InvalidVehicleException();

	return *crankshaft;
}

Game::CylinderHead& Vehicle::getCylinderHead()
{
	Game::CylinderHead* cylinderHead = getCylinderBlock().getCylinderHeadSlot().getPart();

	if(!cylinderHead)
		throw InvalidVehicleException();

	return *cylinderHead;
}

}
