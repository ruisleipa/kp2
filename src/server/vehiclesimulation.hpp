#ifndef SERVER_VEHICLESIMULATION_HPP
#define SERVER_VEHICLESIMULATION_HPP

#include "utils/curve.hpp"
#include "utils/noncopyable.hpp"
#include "vehicle.hpp"
#include "engine.hpp"
#include "intakemanifold.hpp"
#include "exhaustmanifold.hpp"
#include "charger.hpp"

#include "physics/vehicle.hpp"
#include "vehicle.hpp"
#include "engine.hpp"
#include "physics/pipe.hpp"
#include "physics/atmosphere.hpp"
#include "physics/charger.hpp"

class VehicleSimulation: public NonCopyable
{
	public:
		void advance();
		float getTimeInSeconds();
				
		float getPosition();
		float getSpeed();
		
		float getEngineTorque();
		float getEngineSpeedInRpm();
		float getBoostPressure();
		float getIntakeTemperature();
		float getIntakeFlow();
		float getExhaustFlow();
		
		void setIgnition(bool ignition);
		void setThrottleUsage(float usage);
		void setClutchUsage(float usage);
		void setBrakeUsage(float usage);
		void upperGear();
		void lowerGear();
		
		VehicleSimulation(Vehicle& vehicle, int ticksPerSecond = 100);
		
	private:
		const Engine& findEngine();
		const IntakeManifold& findIntakeManifold();
		const ExhaustManifold& findExhaustManifold();
		const Charger* findCharger();
		std::vector<float> getGearRatios();
		int getNeutralGearIndex();
		float getIdleSpeed();
		float getSpeedLimit();
	
		Vehicle& vehicle;
		
		const Engine& enginePart;
		const IntakeManifold& intakeManifoldPart;
		const ExhaustManifold& exhaustManifoldPart;
		const Charger* chargerPart;
		
		Physics::Atmosphere atmosphere;
		Physics::Pipe airFilter;
		Physics::Charger charger;
		Physics::Pipe intakeManifold;
		Physics::Engine engine;
		Physics::Pipe exhaustManifold;
		Physics::Transmission transmission;
		Physics::Clutch clutch;
		Physics::Chassis chassis;
		Physics::Tire frontLeftTire;
		Physics::Tire frontRightTire;
		Physics::Tire backLeftTire;
		Physics::Tire backRightTire;
		Physics::Brake brake;
		Physics::Vehicle physicsVehicle;

};

#endif

