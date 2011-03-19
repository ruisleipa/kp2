#include "engine.hpp"
#include "shared/inifile.hpp"
#include "math_tools.hpp"
#include <fstream>
#include <cmath>

#define TEMP_SIZE TORQUE_CURVE_SIZE

int Engine::load(const std::string& filename)
{
	IniFile file;
	if (file.load(filename))
	{
		std::cerr << "Unable to open \"" << filename << "\"" << std::endl;
		return -1;
	}

	if (!file.getValue("name", m_name)) return -1;
	if (!file.getValue("flywheel_inertia", m_flywheel_inertia)) return -1;
	if (!file.getValue("static_friction", m_static_friction)) return -1;
	if (!file.getValue("rotating_friction", m_rotating_friction)) return -1;
	if (!file.getValue("rev_limiter", m_is_rev_limited)) return -1;
	if (!file.getValue("rev_limit", m_rev_limit)) return -1;
	if (!file.getValue("start_engine_effect", m_start_engine_effect)) return -1;
	if (!file.getValue("idle_speed", m_idle_speed)) return -1;
	if (!file.getValue("idle_throttle", m_idle_throttle)) return -1;
	
	std::string torquefile;
	
	if (!file.getValue("torque_curve_file", torquefile)) return -1;
			
	m_rev_limit *= RPM_TO_RADS;
	m_idle_speed *= RPM_TO_RADS;
	
	if (readTorqueCurve(torquefile) == -1)
		return -1;

	return 0;
}

double Engine::getTorque(float throttle, bool ignition, double revs)
{
	// revs are in rad/s
	float trq = 0.0;

	if ((revs <= m_idle_speed) && (throttle < m_idle_throttle))
		throttle = m_idle_throttle;

	if (m_is_power_on)
	{

		if(ignition)
		{
			if(dabs(revs) < 1.0)
				trq += m_start_engine_effect;
			else
				trq += m_start_engine_effect / fabs(revs);
		}

		if (!m_is_rev_limited || (revs < m_rev_limit))
		{

			// Using linear interpolation
			double rpm_index = revs / 25.0;
			int lowrpm = int (rpm_index);
			if(lowrpm >= 0 && lowrpm < (TORQUE_CURVE_SIZE - 1))
			{

				float low_trq = m_torque_curve[lowrpm];
				float high_trq = m_torque_curve[lowrpm+1];
				// y = kx + b
				trq += throttle * ((rpm_index - double (lowrpm)) * (high_trq - low_trq) + low_trq);
			}
		}
	}				

	trq += revs * m_rotating_friction;

	if (dabs(revs) > 1.0)
		trq += sgn(revs) * m_static_friction;

	return trq;
}

double Engine::getFlywheelInertia()
{
	return m_flywheel_inertia;	
}

Engine::Engine():
	m_name(""),
	m_static_friction(0),
	m_rotating_friction(0),
	m_start_engine_effect(0),
	m_flywheel_inertia(0),
	m_idle_throttle(0),
	m_idle_speed(0),
	m_is_power_on(true),
	m_rev_limit(0),
	m_is_rev_limited(false)
{	

}

std::ostream & operator <<(std::ostream& stream, Engine& engine)
{
	stream << "    --- Engine ---    " << std::endl;
	stream << "Name: " << engine.m_name << std::endl;
	stream << "Idle speed: " << engine.m_idle_speed << "rad/s (" << engine.m_idle_speed * RADS_TO_RPM << "rpm)" << std::endl;
	stream << "Idle throttle: " << engine.m_idle_throttle * 100.0f << "%" << std::endl;
	stream << "Speed limiter: " << (engine.m_is_rev_limited ? "ON" : "OFF") << std::endl;
	stream << "Speed limit: " << engine.m_rev_limit << "rad/s (" << engine.m_rev_limit * RADS_TO_RPM << "rpm)" << std::endl;
	stream << "Flywheel inertia: " << engine.m_flywheel_inertia << "kgm^2" << std::endl;
	stream << "Start engine maximum effect: " << engine.m_start_engine_effect << "W" << std::endl;
	stream << "Static friction factor constant: " << engine.m_static_friction << "Nm" << std::endl;
	stream << "Rotating friction factor constant: " << engine.m_rotating_friction << "Nms" << std::endl;
	
	for(int i = 0; i < TORQUE_CURVE_SIZE; i++)
	{
		stream << engine.m_torque_curve[i] << "Nm @ " << (25 * i) << "rad/s (" << (25 * RADS_TO_RPM * i) << "rpm)" << std::endl;
	}
	return stream;
}

int Engine::readTorqueCurve(const std::string& filename)
{
	/*
	Torque curve file contains the amount of torque for an amount of
	revolutions per minute. First row contains the torque for 0 RPM. With
	each row the RPM goes up by 250.
	*/
	
	/*
	TODO: Maybe the file should contain rpm=torque pairs for arbitrary
	resolution.
	TODO: Maybe we could get rid of these constant sizes.
	*/

	float tmp[TEMP_SIZE];
	std::ifstream file;
	file.open(filename.c_str(), std::ios::in);
	if(!file.is_open())
	{
		#ifdef DEBUG_MODE
		std::cerr << "Couldn't open \"" << path << "\n";
		#endif
		return -1;
	}

	int i = 0;
	while(!file.eof())
	{
		if (i < TEMP_SIZE)
			file >> tmp[i++];
		else
		{
			#ifdef DEBUG_MODE
			std::cerr << "Too long torque curve in \"" << path << "\"\n";
			#endif
			return -1;
		}
	}
	file.close();
	
	//set rest
	while(i < TEMP_SIZE)
	{
		tmp[i++] = 0;
	}
	
	for (int j = 0; j < TORQUE_CURVE_SIZE; ++j)
	{
		// get the amount of Nm @ rpm
		// isn't it amount of Nm @ rad/s?
		
		double rpm = 25.0 * RADS_TO_RPM * j;	
		
		double rpm_index = rpm / 250.0;
		int lowrpm = int (rpm_index);
		if(lowrpm < 0 || lowrpm > (TORQUE_CURVE_SIZE - 2))
			m_torque_curve[j] = 0.0;
		else
		{
			double low_trq = tmp[lowrpm];
			// y = kx + b
			m_torque_curve[j] = (rpm_index - lowrpm) * (tmp[lowrpm + 1] - low_trq) + low_trq;
		}
	}
		
	return 0;
}

