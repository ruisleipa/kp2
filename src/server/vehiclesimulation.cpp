#include "vehiclesimulation.hpp"

void VehicleSimulation::advance()
{
	physicsVehicle->advanceSimulation();
	
	Physics::Air air = exhaustManifold->getAir(1000000000.0);
	
	if(chargerPart)
	{
		charger->calculateSpeed(physicsVehicle->getEngineSpeed());
	}
}

float VehicleSimulation::getTimeInSeconds()
{
	return physicsVehicle->getCurrentTime();
}

float VehicleSimulation::getPosition()
{
	return physicsVehicle->getPos();
}

float VehicleSimulation::getSpeed()
{
	return physicsVehicle->getVel().position;
}

float VehicleSimulation::getEngineTorque()
{
	return engine->getTorque();
}

float VehicleSimulation::getEngineSpeedInRpm()
{
	return physicsVehicle->getEngineSpeed();
}

float VehicleSimulation::getBoostPressure()
{
	return charger->getPressure() / 100000.0;
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

float VehicleSimulation::getLeftTireSlipRatio()
{
	return frontLeftTire->getSlipRatio();
}

float VehicleSimulation::getRightTireSlipRatio()
{
	return frontRightTire->getSlipRatio();
}

void VehicleSimulation::setIgnition(bool ignition)
{
	engine->setIgnition(ignition);
}

void VehicleSimulation::setThrottleUsage(float usage)
{
	engine->setThrottle(usage);
}

void VehicleSimulation::setClutchUsage(float usage)
{
	clutch->setUsage(usage);
}

void VehicleSimulation::setBrakeUsage(float usage)
{
	brake->setUsage(usage);
}

void VehicleSimulation::upperGear()
{
	transmission->upperGear();
}

void VehicleSimulation::lowerGear()
{
	transmission->lowerGear();
}

const Engine& VehicleSimulation::findEngine()
{
	for(size_t i = 0; i < vehicle.getPartCount(); ++i)
	{
		const Part& part = vehicle.getPart(i);
		
		if(part.getType() == "engine")
			return dynamic_cast<const Engine&>(part);
	}
	
	throw VehicleDoesNotWorkException("ENGINE_MISSING");
}

const IntakeManifold& VehicleSimulation::findIntakeManifold()
{
	for(size_t i = 0; i < vehicle.getPartCount(); ++i)
	{
		if(vehicle.getPart(i).getType() == "intakemanifold")
			return dynamic_cast<const IntakeManifold&>(vehicle.getPart(i));
	}
	
	throw VehicleDoesNotWorkException("INTAKEMANIFOLD_MISSING");
}

const ExhaustManifold& VehicleSimulation::findExhaustManifold()
{
	for(size_t i = 0; i < vehicle.getPartCount(); ++i)
	{
		if(vehicle.getPart(i).getType() == "exhaustmanifold")
			return dynamic_cast<const ExhaustManifold&>(vehicle.getPart(i));
	}
	
	throw VehicleDoesNotWorkException("EXHAUSTMANIFOLD_MISSING");
}

const Transmission& VehicleSimulation::findTransmission()
{
	for(size_t i = 0; i < vehicle.getPartCount(); ++i)
	{
		if(vehicle.getPart(i).getType() == "transmission")
			return dynamic_cast<const Transmission&>(vehicle.getPart(i));
	}
	
	throw VehicleDoesNotWorkException("TRANSMISSION_MISSING");
}

const Tire& VehicleSimulation::findTire()
{
	for(size_t i = 0; i < vehicle.getPartCount(); ++i)
	{
		if(vehicle.getPart(i).getType() == "tire")
			return dynamic_cast<const Tire&>(vehicle.getPart(i));
	}
	
	throw VehicleDoesNotWorkException("TIRE_MISSING");
}

const Charger* VehicleSimulation::findCharger()
{
	for(size_t i = 0; i < vehicle.getPartCount(); ++i)
	{
		if(vehicle.getPart(i).getType() == "charger")
			return &(dynamic_cast<const Charger&>(vehicle.getPart(i)));
	}
	
	return 0;
}

VehicleSimulation::VehicleSimulation(Vehicle& vehicle, int ticksPerSecond):
	vehicle(vehicle),
	enginePart(findEngine()),
	intakeManifoldPart(findIntakeManifold()),
	exhaustManifoldPart(findExhaustManifold()),
	transmissionPart(findTransmission()),
	tirePart(findTire()),
	chargerPart(findCharger())
{
	atmosphere.reset(new Physics::Atmosphere());
	airFilter.reset(new Physics::Pipe(*atmosphere,10000));
	
	if(chargerPart)
	{
		charger.reset(new Physics::Charger(*airFilter, chargerPart->getGearRatio(), chargerPart->getAirPerRevolution(), chargerPart->getMaxSpeed()));
		intakeManifold.reset(new Physics::Pipe(*charger, intakeManifoldPart.getFlow()));
	}
	else
	{
		intakeManifold.reset(new Physics::Pipe(*airFilter, intakeManifoldPart.getFlow()));
	}
	
	engine.reset(new Physics::Engine(enginePart.getTorqueCurve(), 1.0, 4, *intakeManifold, enginePart.getIdleSpeed(), 0.1, enginePart.getSpeedLimit(), 2000, 0.22));
	exhaustManifold.reset(new Physics::Pipe(*engine, exhaustManifoldPart.getFlow()));
	transmission.reset(new Physics::Transmission(transmissionPart.getGearRatios(), transmissionPart.getNeutralGearIndex(), 0.8, 3.73, 0.1));
	clutch.reset(new Physics::Clutch(600));
	
	chassis.reset(new Physics::Chassis());
	
	chassis->totalMass = vehicle.getWeight();
	chassis->massOnRear = vehicle.getWeight() / 2.0;
	chassis->centerOfGravityHeight = 0.3;
	chassis->length = vehicle.getModel().getLength();
	chassis->width = vehicle.getModel().getWidth();
	chassis->wheelBase = vehicle.getModel().getWheelbase();
	chassis->dragCoefficient = vehicle.getModel().getDragCoefficient();
	
	frontLeftTire.reset(new Physics::Tire(tirePart.getWeight(), tirePart.getRadius(), tirePart.getRollingResistanceCoefficient(), tirePart.getFrictionCoefficient()));
	frontRightTire.reset(new Physics::Tire(tirePart.getWeight(), tirePart.getRadius(), tirePart.getRollingResistanceCoefficient(), tirePart.getFrictionCoefficient()));
	backLeftTire.reset(new Physics::Tire(tirePart.getWeight(), tirePart.getRadius(), tirePart.getRollingResistanceCoefficient(), tirePart.getFrictionCoefficient()));
	backRightTire.reset(new Physics::Tire(tirePart.getWeight(), tirePart.getRadius(), tirePart.getRollingResistanceCoefficient(), tirePart.getFrictionCoefficient()));

	brake.reset(new Physics::Brake(90, 600000));
	physicsVehicle.reset(new Physics::Vehicle(*engine, *transmission, *clutch, *chassis, *frontLeftTire, *frontRightTire, *backLeftTire, *backRightTire, *brake, *brake, *brake, *brake, ticksPerSecond));
}

