#ifndef _VEHICLE_HPP
#define _VEHICLE_HPP

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include "math_tools.hpp"
#include "shared/thread.hpp"

#include "physics/engine.hpp"
#include "physics/gearbox.hpp"
#include "physics/tire.hpp"
#include "physics/clutch.hpp"
#include "physics/brake.hpp"
#include "physics/chassis.hpp"

class Vehicle
{
	public:
		Vehicle(Engine engine, Gearbox gearbox,
			Clutch clutch, Chassis chassis,
			Tire fltire, Tire frtire,
			Tire bltire, Tire brtire,
			Brake flbrake, Brake frbrake,
			Brake blbrake, Brake brbrake);
		~Vehicle();

		class State
		{
		public:
			tVector<double> vehicle_pos;
			double m_vehicle_angle;	//radians
			double m_flywheel;	//rad/s
			double m_gearbox_out;
			double m_planet_gear;
			double m_f_l_tire;
			double m_f_r_tire;

			State();
			State(double initval);
			State operator*(double factor);
			State& operator+=(State & inc);
			void add(double factor, State& dx);
		};	
		enum corner {FRONT_LEFT, FRONT_RIGHT, REAR_LEFT, REAR_RIGHT};

		int load(const std::string& filename);

		friend int physics(void*);
		
		int startThread();
		int stopThread();

		int toggleTelemetry(bool on);

		tVector<double>& getPos(){return m_current_x.vehicle_pos;}
		void setPos(tVector<double>& pos){m_current_x.vehicle_pos = pos;}
	
		State& getVel(){return m_current_v;}
		void setVel(State& vel){m_current_v = vel;}
		
		State& getAcc(){return m_current_a;}
		void setAcc(State& acc){m_current_a = acc;}
		
		void setBrakeUsage(float usage);
		float getBrakeUsage();
		
		void setThrottle(float throttle);
		float getThrottle();
		
		void setClutchUsage(float usage);
		float getClutchUsage();
		
		void setIgnition(bool ignition);
		float getIgnition();
		
		void setGear(int gear);
		float getGear();
		
		float getEngineSpeed();

	private:	
		Engine m_engine;
		Gearbox m_gearbox;
		Clutch m_clutch;
		Chassis m_chassis;
		Tire m_tires[4];
		Brake m_brakes[4];

		State m_current_x, m_current_v, m_current_a;
		void getDerivates(State*, State*, State*);
		Thread m_enginethread;
		bool m_simulate;
		
		float m_brake_usage;
		float m_throttle;
		float m_clutch_usage;
		bool m_ignition;
		int m_current_gear;
		
		bool m_log_telemetry;
		std::ofstream m_tel_out;
};

#endif
