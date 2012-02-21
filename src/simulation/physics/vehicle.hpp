#ifndef _VEHICLE_HPP
#define _VEHICLE_HPP

#include <string>
#include <fstream>

#include "math_tools.hpp"

#include "engine.hpp"
#include "transmission.hpp"
#include "tire.hpp"
#include "clutch.hpp"
#include "brake.hpp"
#include "chassis.hpp"

#include "utils/noncopyable.hpp"

namespace Physics
{

class Vehicle: public NonCopyable
{
	public:
		Vehicle(Engine& engine, Transmission& transmission, Clutch& clutch,
			Chassis& chassis, Tire& frontLeftTire, Tire& frontRightTire,
			Tire& backLeftTire, Tire& backRightTire, Brake& frontLeftBrake,
			Brake& frontRightBrake, Brake& backLeftBrake,
			Brake& backRightBrake, int ticksPerSecond);
		
		class State
		{
			public:
				double vehiclePosition;
				double vehicleVelocity;
				double vehicleAcceleration;
				double engineSpeed;
				double backWheelSpeed;
				double frontWheelSpeed;

				State();
		};
		
		class Derivative
		{
			public:
				double vehicleVelocity;
				double vehicleAcceleration;
				double engineAcceleration;
				double backWheelAcceleration;
				double frontWheelAcceleration;
				
				Derivative operator+(const Derivative& d);
				Derivative operator*(double f);
				
				Derivative();
		};
		
		double getPosition(){return currentState.vehiclePosition;}
		double getVelocity(){return currentState.vehicleVelocity;}
		
		void setBrakeUsage(float usage);
		float getBrakeUsage();

		float getEngineSpeed();
		
		void advanceSimulation();
		int getCurrentStep();
		float getCurrentTime();
		int getLagInSteps(double realTime);

	private:	
		Engine& engine;
		Transmission& transmission;
		Clutch& clutch;
		Chassis& chassis;
		Tire& frontLeftTire;
		Tire& frontRightTire;
		Tire& backLeftTire;
		Tire& backRightTire;
		Brake& frontLeftBrake;
		Brake& frontRightBrake;
		Brake& backLeftBrake;
		Brake& backRightBrake;

		State currentState;
		Derivative evaluate(const State& initial, double dt, const Derivative& d);
		Derivative integrateRK4(double dt);
		Derivative integrateEuler(double dt);
		Derivative calculateAccelerations(const State& state);
		
		float m_brake_usage;
		
		int step;
		
		const int TICKS_PER_SECOND;
		
		std::ofstream telemetry;
};

};

#endif
