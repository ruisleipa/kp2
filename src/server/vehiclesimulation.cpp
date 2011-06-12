#include "vehiclesimulation.hpp"

void VehicleSimulation::advance()
{
	physicsVehicle.advanceSimulation();
	
	Physics::Air air = exhaustManifold.getAir(1000000000.0);
	
	if(chargerPart)
	{
		charger.calculateSpeed(physicsVehicle.getEngineSpeed());
	}
}

float VehicleSimulation::getTimeInSeconds()
{
	return physicsVehicle.getCurrentTime();
}

float VehicleSimulation::getPosition()
{
	return physicsVehicle.getPos();
}

float VehicleSimulation::getSpeed()
{
	return physicsVehicle.getVel().position;
}

float VehicleSimulation::getEngineTorque()
{
	return engine.getTorque();
}

float VehicleSimulation::getEngineSpeedInRpm()
{
	return physicsVehicle.getEngineSpeed();
}

float VehicleSimulation::getBoostPressure()
{
	return charger.getPressure() / 100000.0;
}

float VehicleSimulation::getIntakeTemperature()
{
	return 0;
}

float VehicleSimulation::getIntakeFlow()
{
	return 0;
}

float VehicleSimulation::getExhaustFlow()
{
	return 0;
}

void VehicleSimulation::setIgnition(bool ignition)
{
	engine.setIgnition(ignition);
}

void VehicleSimulation::setThrottleUsage(float usage)
{
	engine.setThrottle(usage);
}

void VehicleSimulation::setClutchUsage(float usage)
{
	clutch.setUsage(usage);
}

void VehicleSimulation::setBrakeUsage(float usage)
{
	brake.setUsage(usage);
}

void VehicleSimulation::upperGear()
{
	transmission.upperGear();
}

void VehicleSimulation::lowerGear()
{
	transmission.lowerGear();
}

const Engine& VehicleSimulation::findEngine()
{
	for(size_t i = 0; i < vehicle.getPartCount(); ++i)
	{
		if(vehicle.getPart(i).getType() == "engine")
			return vehicle.getPart(i).getModel<Engine>();
	}
	
	throw VehicleDoesNotWorkException("ENGINE_MISSING");
}

const IntakeManifold& VehicleSimulation::findIntakeManifold()
{
	for(size_t i = 0; i < vehicle.getPartCount(); ++i)
	{
		if(vehicle.getPart(i).getType() == "intakemanifold")
			return vehicle.getPart(i).getModel<IntakeManifold>();
	}
	
	throw VehicleDoesNotWorkException("INTAKEMANIFOLD_MISSING");
}

const ExhaustManifold& VehicleSimulation::findExhaustManifold()
{
	for(size_t i = 0; i < vehicle.getPartCount(); ++i)
	{
		if(vehicle.getPart(i).getType() == "exhaustmanifold")
			return vehicle.getPart(i).getModel<ExhaustManifold>();
	}
	
	throw VehicleDoesNotWorkException("EXHAUSTMANIFOLD_MISSING");
}

const Charger* VehicleSimulation::findCharger()
{
	for(size_t i = 0; i < vehicle.getPartCount(); ++i)
	{
		if(vehicle.getPart(i).getType() == "charger")
			return &(vehicle.getPart(i).getModel<Charger>());
	}
	
	return 0;
}

std::vector<float> VehicleSimulation::getGearRatios()
{
	std::vector<float> gearRatios;
	gearRatios.push_back(-2.86);
	gearRatios.push_back(0);
	gearRatios.push_back(3.9);
	gearRatios.push_back(2.6);
	gearRatios.push_back(1.9);
	gearRatios.push_back(1.5);
	gearRatios.push_back(1.3);
	
	return gearRatios;
}

int VehicleSimulation::getNeutralGearIndex()
{
	return 1;
}

float VehicleSimulation::getIdleSpeed()
{
	return 1000;
}

float VehicleSimulation::getSpeedLimit()
{
	return 6000;
}

VehicleSimulation::VehicleSimulation(Vehicle& vehicle, int ticksPerSecond):
	vehicle(vehicle),
	enginePart(findEngine()),
	intakeManifoldPart(findIntakeManifold()),
	exhaustManifoldPart(findExhaustManifold()),
	chargerPart(findCharger()),
	atmosphere(),
	airFilter(atmosphere, 1000000),
	charger(airFilter, 0, 0, 0),
	intakeManifold(airFilter, intakeManifoldPart.getFlow()),
	engine(enginePart.getTorqueCurve(), 1.0, 4, intakeManifold, getIdleSpeed(), 0.1, getSpeedLimit(), 2000, 0.22),
	exhaustManifold(engine, exhaustManifoldPart.getFlow()),
	transmission(getGearRatios(), getNeutralGearIndex(), 0.8, 4.22, 0.1),
	clutch(600),
	chassis(),
	frontLeftTire(9, 0.3048, 0.015),
	frontRightTire(9, 0.3048, 0.015),
	backLeftTire(9, 0.3048, 0.015),
	backRightTire(9, 0.3048, 0.015),
	brake(90, 600000),
	physicsVehicle(engine, transmission, clutch, chassis, frontLeftTire, frontRightTire, backLeftTire, backRightTire, brake, brake, brake, brake, ticksPerSecond)
{
	if(chargerPart)
	{
		charger = Physics::Charger(airFilter, chargerPart->getGearRatio(), chargerPart->getAirPerRevolution(), chargerPart->getMaxSpeed());
		intakeManifold = Physics::Pipe(charger, intakeManifoldPart.getFlow());
	}
	
	float idleSpeed = 1000;
	float speedLimit = 8000;
	
	chassis.totalMass = vehicle.getWeight();
	chassis.massOnRear = vehicle.getWeight() / 2.0;
	chassis.centerOfGravityHeight = 0.3;
	chassis.length = vehicle.getModel().getLength();
	chassis.width = vehicle.getModel().getWidth();
	chassis.wheelBase = vehicle.getModel().getWheelbase();
	chassis.dragCoefficient = vehicle.getModel().getDragCoefficient();
}

