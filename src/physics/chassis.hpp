#ifndef _CHASSIS_HPP
#define _CHASSIS_HPP

#include <iostream>
#include <string>

class Chassis
{
	public:
		int load(const std::string& filename);
		
		float getTotalMass();
		float getRearMass();
		float getWheelbase();
		float getAeroDrag();
		float getCenterOfGravityHeight();

		Chassis();

		friend std::ostream& operator<<(std::ostream& stream,const Chassis& brake);

	private:
		float m_mass;
		float m_center_of_gravity_height;
		float m_length;
		float m_width;
		float m_wheelbase;
		float m_mass_rear; // how much from the total mass is on the rear axle?
		float m_aero_drag;

};

#endif
