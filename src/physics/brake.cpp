#include "brake.hpp"

#include <cmath>
#include "math_tools.hpp"


float Brake::getTorque(float usage, float disc_speed)
{
	float return_value = usage * -m_cof * disc_speed;
	
	if (fabs(return_value) > m_max_torque)
		return_value = sgn(return_value) * m_max_torque;
		
	return return_value;
}

Brake::Brake():
	m_cof(0.0),
	m_max_torque(0.0)
{	

}
