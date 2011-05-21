#ifndef _VEHICLE_HPP
#define _VEHICLE_HPP

#include <string>

#include "math_tools.hpp"

#include "engine.hpp"
#include "transmission.hpp"
#include "tire.hpp"
#include "clutch.hpp"
#include "brake.hpp"
#include "chassis.hpp"

namespace Physics
{

class Vehicle
{
	public:
		Vehicle(Engine& engine, Transmission& transmission, Clutch& clutch,
			Chassis& chassis, Tire& frontLeftTire, Tire& frontRightTire,
			Tire& backLeftTire, Tire& backRightTire, Brake& frontLeftBrake,
			Brake& frontRightBrake, Brake& backLeftBrake,
			Brake& backRightBrake);
		
		class State
		{
			public:
				double position;
				double m_flywheel;	//rad/s
				double gearbox_out;
				double m_planet_gear;
				double m_f_l_tire;
				double m_f_r_tire;

				State();
				void add(double factor, State& dx);
		};	
		
		double getPos(){return m_current_x.position;}
		void setPos(double pos){m_current_x.position = pos;}
	
		
	
		State& getState(){return m_current_x;}
		State& getVel(){return m_current_v;}
		State& getAcc(){return m_current_a;}
		
		void setBrakeUsage(float usage);
		float getBrakeUsage();

		float getEngineSpeed();
		
		void advanceSimulation();
		int getCurrentStep();
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

		State m_current_x, m_current_v, m_current_a;
		void getDerivates(State*, State*, State*);
		
		float m_brake_usage;
		
		int step;
};

};

#endif
