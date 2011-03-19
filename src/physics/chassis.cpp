#include "chassis.hpp"

#include <cmath>
#include "math_tools.hpp"
#include "shared/inifile.hpp"

int Chassis::load(const std::string& filename)
{
	IniFile file;
	if (file.load(filename))
	{
		std::cerr << "Unable to open \"" << filename << "\"\n";
		return -1;
	}

	if (!file.getValue("vehicle_width", m_width)) return -1;
	if (!file.getValue("vehicle_length", m_length)) return -1;
	if (!file.getValue("vehicle_mass", m_mass)) return -1;
	if (!file.getValue("center_of_gravity", m_center_of_gravity_height)) return -1;
	if (!file.getValue("wheelbase", m_wheelbase)) return -1;
	if (!file.getValue("mass_rear", m_mass_rear)) return -1;
	if (!file.getValue("aerodynamic_drag", m_aero_drag)) return -1;

	return 0;
}

float Chassis::getTotalMass()
{
	return m_mass;
}

float Chassis::getRearMass()
{
	return m_mass_rear;
}

float Chassis::getWheelbase()
{
	return m_wheelbase;
}

float Chassis::getAeroDrag()
{
	return m_aero_drag;
}

float Chassis::getCenterOfGravityHeight()
{
	return m_center_of_gravity_height;
}

std::ostream& operator<<(std::ostream& stream,const Chassis& chassis)
{
	stream << "    --- Chassis ---    " << std::endl;
	stream << "Total mass: " << chassis.m_mass << "kg" << std::endl;
	stream << "Height of the mass point: " << chassis.m_center_of_gravity_height << "m"<< std::endl;
	stream << "Length: " << chassis.m_length << "m"<< std::endl;
	stream << "Width: " << chassis.m_width << "m"<< std::endl;
	stream << "Wheelbase: " << chassis.m_wheelbase << "m"<< std::endl;
	stream << "Aerodynamic drag coefficient: " << chassis.m_aero_drag << "kg/m"<< std::endl;
	return stream;
}

Chassis::Chassis():
	m_mass(0),
	m_center_of_gravity_height(0),
	m_length(0),
	m_width(0),
	m_wheelbase(0),
	m_mass_rear(0),
	m_aero_drag(0)
{	

}
