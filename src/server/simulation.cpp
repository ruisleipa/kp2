#include "simulation.hpp"

#include "physics/vehicle.hpp"
#include "vehicle.hpp"
#include "engine.hpp"
#include "physics/pipe.hpp"
#include "physics/atmosphere.hpp"
#include "physics/charger.hpp"

void Simulation::run()
{		
	const Engine& enginePart = findEngine();
	const IntakeManifold& intakeManifoldPart = findIntakeManifold();
	const ExhaustManifold& exhaustManifoldPart = findExhaustManifold();
	const Charger* chargerPart = findCharger();
	
	Physics::Atmosphere atmosphere;

	//TODO: get real value for air filter capacity
	Physics::Pipe airFilter(atmosphere, 1000000);
	
	Physics::Charger charger(airFilter, 0, 0, 0);
	Physics::Pipe intakeManifold(airFilter, intakeManifoldPart.getFlow());
	
	if(chargerPart)
	{
		charger = Physics::Charger(airFilter, chargerPart->getGearRatio(), chargerPart->getAirPerRevolution(), chargerPart->getMaxSpeed());
		intakeManifold = Physics::Pipe(charger, intakeManifoldPart.getFlow());
	}
	
	float idleSpeed = 1000;
	float speedLimit = 8000;
	
	Physics::Engine engine(enginePart.getTorqueCurve(), 1.0, 4, intakeManifold, idleSpeed, 0.3, speedLimit, 2000, 0.22);
	
	Physics::Pipe exhaustManifold(engine, exhaustManifoldPart.getFlow());
	
	std::vector<float> gearRatios;
	gearRatios.push_back(0);
	Physics::Transmission transmission(gearRatios, 0, 0.8, 4.22, 0.1);
	
	Physics::Clutch clutch(600);
	
	Physics::Chassis chassis;
	
	chassis.totalMass = vehicle.getWeight();
	chassis.massOnRear = vehicle.getWeight() / 2.0;
	chassis.centerOfGravityHeight = 0.3;
	chassis.length = vehicle.getModel().getLength();
	chassis.width = vehicle.getModel().getWidth();
	chassis.wheelBase = vehicle.getModel().getWheelbase();
	chassis.dragCoefficient = vehicle.getModel().getDragCoefficient();
	
	Physics::Tire frontLeftTire(9, 0.3048, 0.015);
	Physics::Tire frontRightTire(9, 0.3048, 0.015);
	Physics::Tire backLeftTire(9, 0.3048, 0.015);
	Physics::Tire backRightTire(9, 0.3048, 0.015);
	
	Physics::Brake brake(0.8, 6000);
	
	Physics::Vehicle vehicle(engine, transmission, clutch, chassis, frontLeftTire, frontRightTire, backLeftTire, backRightTire, brake, brake, brake, brake);

	int nextSpeed = 0;
	const int speedStep = 25;
	
	while(vehicle.getLagInSteps(60.0) > 0)
	{
		vehicle.advanceSimulation();
	
		Physics::Air air = exhaustManifold.getAir(1000000000.0);
		
		if(chargerPart)
		{
			charger.calculateSpeed(vehicle.getEngineSpeed());
		}
		
		if(vehicle.getEngineSpeed() < idleSpeed)
			engine.setIgnition(true);
		else
			engine.setIgnition(false);
			
		if(vehicle.getEngineSpeed() >= idleSpeed)
			engine.setThrottle(1.0);
			
		if(vehicle.getEngineSpeed() >= nextSpeed && vehicle.getEngineSpeed() > 1000)
		{
			float speed = vehicle.getEngineSpeed();
			
			float torque = engine.getTorque();
			
			torqueData.addPoint(speed, torque);
			powerData.addPoint(speed, torque * (vehicle.getEngineSpeed() * RPM_TO_RADS) / 1000.0);
			intakeData.addPoint(speed, engine.calculateMaxFromIntakeManifold());
			exhaustData.addPoint(speed, engine.calculateMaxToExhaustManifold());
			
			nextSpeed += speedStep;
		}
	}
}

const Curve& Simulation::getTorqueData()
{
	return torqueData;
}

const Curve& Simulation::getPowerData()
{
	return powerData;
}

const Curve& Simulation::getIntakeData()
{
	return intakeData;
}

const Curve& Simulation::getExhaustData()
{
	return exhaustData;
}

const Engine& Simulation::findEngine()
{
	for(size_t i = 0; i < vehicle.getPartCount(); ++i)
	{
		if(vehicle.getPart(i).getType() == "engine")
			return vehicle.getPart(i).getModel<Engine>();
	}
	
	throw VehicleDoesNotWorkException("ENGINE_MISSING");
}

const IntakeManifold& Simulation::findIntakeManifold()
{
	for(size_t i = 0; i < vehicle.getPartCount(); ++i)
	{
		if(vehicle.getPart(i).getType() == "intakemanifold")
			return vehicle.getPart(i).getModel<IntakeManifold>();
	}
	
	throw VehicleDoesNotWorkException("INTAKEMANIFOLD_MISSING");
}

const ExhaustManifold& Simulation::findExhaustManifold()
{
	for(size_t i = 0; i < vehicle.getPartCount(); ++i)
	{
		if(vehicle.getPart(i).getType() == "exhaustmanifold")
			return vehicle.getPart(i).getModel<ExhaustManifold>();
	}
	
	throw VehicleDoesNotWorkException("EXHAUSTMANIFOLD_MISSING");
}

const Charger* Simulation::findCharger()
{
	for(size_t i = 0; i < vehicle.getPartCount(); ++i)
	{
		if(vehicle.getPart(i).getType() == "charger")
			return &(vehicle.getPart(i).getModel<Charger>());
	}
	
	return 0;
}

Simulation::Simulation(Vehicle& vehicle):
	vehicle(vehicle)
{

}

