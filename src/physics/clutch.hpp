#ifndef _CLUTCH_HPP
#define _CLUTCH_HPP

#include <iostream>
#include <string>

class Clutch
{
	public:
		
		int load(const std::string& filename);

		float getTorque(float usage, float input_speed, float output_speed);

		friend std::ostream& operator<<(std::ostream& stream, Clutch& clutch);
				
		Clutch();	
		
	private:
		std::string m_name;
		float m_max_torque;

};

#endif
