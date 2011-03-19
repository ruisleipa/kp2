#ifndef _GEARBOX_HPP
#define _GEARBOX_HPP

#include <iostream>
#include <string>
#include <cstdlib>

const int MAX_GEARS=9;
const char REVERSE_CHAR='R';
const char NEUTRAL_CHAR='N';

class Gearbox
{
	public:	
		int load(const std::string& filename);
	
		float getRatio(int gear);
		int getNeutralGear();
		int getGearCount();
		float getDifferentialRatio();
		float getEfficiency();
		float getDriveshaftInertia();
		
		Gearbox();	
	
		friend std::ostream & operator<<(std::ostream &, Gearbox &);
		
	private:
		std::string m_name;
		float m_differential_ratio;
		float m_efficiency;
		float m_driveshaft_inertia;

		float m_gear_ratios[MAX_GEARS];
		int m_gear_count;
		int m_neutral_gear;
};

#endif
