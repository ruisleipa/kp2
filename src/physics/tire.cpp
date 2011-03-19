#include "tire.hpp"
#include "math_tools.hpp"
#include "shared/inifile.hpp"
#include <fstream>

Tire::Tire():
	m_sratio(0),
	m_load(0),
	m_name(""),
	m_radius(0),
	m_inertia(0),
	m_roll_friction(0)
{

}

int Tire::load(const std::string& filename)
{
	int tire_width;
	int profile;
	int wheel_size;
	float mass;
	
	IniFile file;
	if (file.load(filename))
	{
		std::cerr << "Unable to open \"" << filename << "\"" << std::endl;
		return -1;
	}

	if (!file.getValue("name", m_name)) return -1;
	if (!file.getValue("tire_width", tire_width)) return -1;
	if (!file.getValue("profile", profile)) return -1;
	if (!file.getValue("wheel_size", wheel_size)) return -1;
	if (!file.getValue("mass", mass)) return -1;
	if (!file.getValue("roll_friction", m_roll_friction)) return -1;
	
	std::stringstream ss;
	
	for (int i = 0; i < 13; ++i)
	{
		ss.str("");
		ss << "b";
		ss << i;
		
		if (!file.getValue(ss.str(), m_b[i])) return -1;
	}

	m_radius = float (wheel_size) * 0.0254f;
	m_radius += 2.0f * ((float (tire_width) * 0.001f)*(float (profile) * 0.01f));
	m_radius /= 2.0f;
	m_inertia = 0.5f * mass * m_radius * m_radius;

	return 0;
}

double Tire::getRadius()
{
	return m_radius;
}

double Tire::getInertia()
{
	return m_inertia;
}

double Tire::getFriction(double load)
{
	double Fz = 0.001 * load;
	// This is an estimate of the peak, longitudinal coefficient of friction
	double Up = m_b[1] * Fz + m_b[2];
	double D = Up * Fz;
	double C = m_b[0] * (Fz * m_b[1] + m_b[2]);
	double B = (m_b[3] * Fz + m_b[4]) * expf(-m_b[5] * Fz);
	if (C == 0.0f)
		B = 999999.9f;
	else
		B /= C;
	double S = m_sratio + m_b[9] * Fz + m_b[10];
	double E = m_b[6] * Fz * Fz + m_b[7] * Fz  + m_b[8];
	
	return D * sin(m_b[0] * atanf(S * B + E * (atanf(S * B) - S * B)));
	
}

double Tire::getRollingResist(double load,double speed)
{
	if (fabs(speed) > 1.0f)
		return m_roll_friction * load;
	else
		return 0.0f;
}	

void Tire::test_pacejka()
{
	/*std::cout << "TESTING PACEJKA\n";
	double temp_load = load;
	double temp_sratio = sratio;
	load = 1000.0f;
	for (double x = -1000.0; x <= 1000.0; x += 25.0)
	{
		sratio = x;
		std::cout << "f(" << x << ", 1000N) = " << Friction() << "\n";
	}
	std::cout << "--------------------\n";
	load = temp_load;
	sratio = temp_sratio;*/
}

std::ostream& operator<<(std::ostream& stream,const Tire& tire)
{
	stream << "    --- Tire model ---    " << std::endl;
	stream << "Tire name: " << tire.m_name << std::endl;
	stream << "Tire radius: " << tire.m_radius << "m" << std::endl;
	stream << "Tire inertia: " << tire.m_inertia << "kgm^2" << std::endl;
   
	for(int i = 0; i < 13 ; ++i)
	{
		stream << "Tire constant b" << i << ": ";
		stream << tire.m_b[i] << std::endl;
	}


	return stream;
}

