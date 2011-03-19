#ifndef _ENGINE_HPP
#define _ENGINE_HPP

#include <iostream>
#include <string>

#define TORQUE_CURVE_SIZE 64

class Engine
{
	public:
		int load(const std::string& filename);
		
		double getTorque(float throttle, bool ignition, double revs);
		double getFlywheelInertia();
		
		Engine();

		friend std::ostream& operator<<(std::ostream& stream, Engine& engine);	

	private:
		int readTorqueCurve(const std::string& filename);
		
		// static data
		std::string m_name;
		float m_static_friction;
		float m_rotating_friction;
		float m_start_engine_effect;
		float m_flywheel_inertia;
		float m_idle_throttle;
		float m_idle_speed;
		bool m_is_power_on;
		double m_rev_limit;
		bool m_is_rev_limited;
		double m_torque_curve[TORQUE_CURVE_SIZE]; // 0-1575 rad/s, at 25 rad/s steps
};


#endif
