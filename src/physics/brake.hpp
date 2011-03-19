#ifndef _BRAKE_HPP
#define _BRAKE_HPP

#include <iostream>
#include <string>

class Brake
{
	public:
		int load(const std::string& filename);
		float getTorque(float usage, float disc_speed);
		
		Brake();

		friend std::ostream& operator<<(std::ostream& stream,const Brake& brake);
		
	private:
		std::string m_name;
		float m_cof;
		float m_max_torque;

};

#endif
