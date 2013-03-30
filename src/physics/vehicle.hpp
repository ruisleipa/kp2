#ifndef PHYSICS_VEHICLE_HPP
#define PHYSICS_VEHICLE_HPP

#include "game/vehicle.hpp"

#include "units.hpp"
#include "starter.hpp"
#include "flywheel.hpp"
#include "engine.hpp"

namespace Physics
{

class Vehicle
{
	public:
		class InvalidVehicleException
		{

		};

		class State
		{
			public:
				Seconds time;
				NewtonMeters engineTorque;
				Watts enginePower;
				RadiansPerSecond engineSpeed;
		};

		void advanceSimulation();
		const State& getState();

		Vehicle(const Game::Vehicle& vehicle);

	private:
		int findNumberOfCylinders();
		Engine::CylinderGeometry findCylinderGeometry();
		Game::CylinderBlock& getCylinderBlock();
		Game::CylinderHead& getCylinderHead();
		Game::Crankshaft& getCrankshaft();
		Game::Chassis& getChassis();

		const Game::Vehicle& vehicle;

		State state;

		Starter starter;
		Flywheel flywheel;
		Engine engine;

};

}

#endif
