#ifndef SERVER_SIMULATION_HPP
#define SERVER_SIMULATION_HPP

#include "utils/curve.hpp"
#include "vehicle.hpp"
#include "engine.hpp"
#include "intakemanifold.hpp"
#include "exhaustmanifold.hpp"
#include "charger.hpp"

class Simulation
{
	public:
		void run();
		
		const Curve& getTorqueData();
		const Curve& getPowerData();
		const Curve& getIntakeData();
		const Curve& getExhaustData();
		
		Simulation(Vehicle& vehicle);
		
	private:
		const Engine& findEngine();
		const IntakeManifold& findIntakeManifold();
		const ExhaustManifold& findExhaustManifold();
		const Charger* findCharger();
	
		Vehicle& vehicle;
		
		Curve torqueData;
		Curve powerData;
		Curve intakeData;
		Curve exhaustData;

};

#endif // SERVER_SIMULATION_HPP

