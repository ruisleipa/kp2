#ifndef SERVER_VEHICLESIMULATION_HPP
#define SERVER_VEHICLESIMULATION_HPP

#include "utils/curve.hpp"
#include "utils/noncopyable.hpp"
#include "vehicle.hpp"
#include "engine.hpp"
#include "intakemanifold.hpp"
#include "exhaustmanifold.hpp"
#include "transmission.hpp"
#include "tire.hpp"
#include "charger.hpp"

#include "physics/vehicle.hpp"
#include "vehicle.hpp"
#include "engine.hpp"
#include "physics/pipe.hpp"
#include "physics/atmosphere.hpp"
#include "physics/charger.hpp"

#include <tr1/memory>

using std::tr1::shared_ptr;

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
		float getLeftTireSlipRatio();
		float getRightTireSlipRatio();
		
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
		const Transmission& findTransmission();
		const Tire& findTire();
		const Charger* findCharger();
	
		Vehicle& vehicle;
		
		const Engine& enginePart;
		const IntakeManifold& intakeManifoldPart;
		const ExhaustManifold& exhaustManifoldPart;
		const Transmission& transmissionPart;
		const Tire& tirePart;
		const Charger* chargerPart;
		
		shared_ptr<Physics::Atmosphere> atmosphere;
		shared_ptr<Physics::Pipe> airFilter;
		shared_ptr<Physics::Charger> charger;
		shared_ptr<Physics::Pipe> intakeManifold;
		shared_ptr<Physics::Engine> engine;
		shared_ptr<Physics::Pipe> exhaustManifold;
		shared_ptr<Physics::Transmission> transmission;
		shared_ptr<Physics::Clutch> clutch;
		shared_ptr<Physics::Chassis> chassis;
		shared_ptr<Physics::Tire> frontLeftTire;
		shared_ptr<Physics::Tire> frontRightTire;
		shared_ptr<Physics::Tire> backLeftTire;
		shared_ptr<Physics::Tire> backRightTire;
		shared_ptr<Physics::Brake> brake;
		shared_ptr<Physics::Vehicle> physicsVehicle;

};

#endif

