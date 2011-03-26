#ifndef _VEHICLE_HPP
#define _VEHICLE_HPP

#include <string>

#include "math_tools.hpp"

#include "engine.hpp"
#include "gearbox.hpp"
#include "tire.hpp"
#include "clutch.hpp"
#include "brake.hpp"
#include "chassis.hpp"

class Vehicle
{
	public:
		Vehicle(Engine& engine, Gearbox& gearbox, Clutch& clutch,
			Chassis& chassis, Tire& frontLeftTire, Tire& frontRightTire,
			Tire& backLeftTire, Tire& backRightTire, Brake& frontLeftBrake,
			Brake& frontRightBrake, Brake& backLeftBrake,
			Brake& backRightBrake);
		
		class State
		{
			public:
				double position;
				double m_flywheel;	//rad/s
				double m_gearbox_out;
				double m_planet_gear;
				double m_f_l_tire;
				double m_f_r_tire;

				State();
				void add(double factor, State& dx);
		};	
		
		tVector<double>& getPos(){return m_current_x.position;}
		void setPos(tVector<double>& pos){m_current_x.position = pos;}
	
		State& getVel(){return m_current_v;}
		State& getAcc(){return m_current_a;}
		
		void setBrakeUsage(float usage);
		float getBrakeUsage();
		
		void setClutchUsage(float usage);
		float getClutchUsage();
		
		void setGear(int gear);
		int getGear();
		
		float getEngineSpeed();
		
		void advanceSimulation();
		int getCurrentStep();
		int getLagInSteps(double realTime);

	private:	
		Engine& engine;
		Gearbox& gearbox;
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
		float m_throttle;
		float m_clutch_usage;
		bool m_ignition;
		int m_current_gear;
		
		int step;
};

#endif
