#ifndef _TIRE_HPP
#define _TIRE_HPP

#include <iostream>
#include <string>
#include <cmath>

class Tire
{
	public:
		Tire();
		int load(const std::string& filename);

		double getFriction(double load);
		double getRadius();
		double getInertia();
		double getRollingResist(double load,double speed);
	
		friend std::ostream& operator<<(std::ostream& stream,const Tire& tire);
		void test_pacejka();
		double m_sratio;	// in procents!!
	private:
		
		double m_load;
		
		// static data
		std::string m_name;
		double m_radius;
		double m_inertia;
		double m_b[13];
		double m_roll_friction;
};

#endif
