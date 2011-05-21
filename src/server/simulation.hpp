#ifndef SERVER_SIMULATION_HPP
#define SERVER_SIMULATION_HPP

#include "utils/curve.hpp"
#include "vehicle.hpp"
#include "engine.hpp"
#include "intakemanifold.hpp"
#include "exhaustmanifold.hpp"

class Simulation
{
	public:
		void run();
		
		const Curve& getTorqueData();
		const Curve& getPowerData();
		
		Simulation(Vehicle& vehicle);
		
	private:
		const Engine& findEngine();
		const IntakeManifold& findIntakeManifold();
		const ExhaustManifold& findExhaustManifold();
	
		Vehicle& vehicle;
		
		Curve torqueData;
		Curve powerData;

};

#endif // SERVER_SIMULATION_HPP

