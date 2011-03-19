#include "brake.hpp"

#include <cmath>
#include "math_tools.hpp"
#include "shared/inifile.hpp"

int Brake::load(const std::string& filename)
{
	IniFile file;
	if (file.load(filename))
	{
		std::cerr << "Unable to open \"" << filename << "\"\n";
		return -1;
	}

	if (!file.getValue("name", m_name)) return -1;
	if (!file.getValue("cof", m_cof)) return -1;
	if (!file.getValue("max_torque", m_max_torque)) return -1;

	return 0;
}

float Brake::getTorque(float usage, float disc_speed)
{
	float return_value = usage * -m_cof * disc_speed;
	
	if (fabs(return_value) > m_max_torque)
		return_value = sgn(return_value) * m_max_torque;
		
	return return_value;
}

std::ostream& operator<<(std::ostream& stream,const Brake& brake)
{
    stream
    <<  "\n"
    <<  "    --- Brake ---    \n"
    <<  "Brake friction factor constant: " << brake.m_cof << "\n"
    <<  "Brake maximum load: " << brake.m_max_torque << "Nm\n";
    return stream;
}

Brake::Brake():
	m_name(""),
	m_cof(0.0),
	m_max_torque(0.0)
{	

}
