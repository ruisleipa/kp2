#include "clutch.hpp"
#include "shared/inifile.hpp"
#include "math_tools.hpp"

#include <cmath>

int Clutch::load(const std::string& filename)
{	
	IniFile file;
	if (file.load(filename))
	{
		std::cerr << "Unable to open \"" << filename << "\"\n";
		return -1;
	}

	if (!file.getValue("name", m_name)) return -1;
	if (!file.getValue("max_torque", m_max_torque)) return -1;

	return 0;
}

float Clutch::getTorque(float usage, float input_speed, float output_speed)
{
	return pow(usage, 3) * m_max_torque * sgn(input_speed - output_speed);
}

std::ostream& operator<<(std::ostream& stream, Clutch& clutch)
{
	stream <<  "    --- Clutch ---    " << std::endl;
	stream <<  "Clutch maximum load: " << clutch.m_max_torque << "Nm" << std::endl;
	return stream;
}

Clutch::Clutch():
	m_name(""),
	m_max_torque(0)
{

}

