#include "gearbox.hpp"
#include "shared/inifile.hpp"
#include "math_tools.hpp"
#include <iostream>

Gearbox::Gearbox():
	m_name(""),
	m_differential_ratio(0),
	m_efficiency(0),
	m_driveshaft_inertia(0),
	m_gear_count(0),
	m_neutral_gear(0)
{

}

int Gearbox::load(const std::string& filename)
{
	std::string indfile, sfile;
	int neutral_gear;

	IniFile in;
	if (in.load(filename))
	{
		#ifdef DEBUG_MODE
		std::cerr << "Unable to open \"" << filename << "\"\n";
		#endif
		return -1;
	}

	if (!in.getValue("name", m_name)) return -1;
	if (!in.getValue("differential_ratio", m_differential_ratio)) return -1;
	if (!in.getValue("efficiency", m_efficiency)) return -1;
	if (!in.getValue("driveshaft_inertia", m_driveshaft_inertia)) return -1;
	if (!in.getValue("gear_count", m_gear_count)) return -1;
	if (!in.getValue("neutral_gear", m_neutral_gear)) return -1;
	
	if (m_gear_count > MAX_GEARS)
	{
		std::cerr << "Too many gears in \"" << filename << "\" (" << m_gear_count << "/" << MAX_GEARS << ")\n";
		return -1;
	}
	
	std::stringstream ss;
	
	for(int i = 0; i < m_gear_count ; ++i)
	{
		ss.str("");
		ss << "gear_";
		ss << i;
		
		if (!in.getValue(ss.str(),m_gear_ratios[i]))
			return -1;
	}
	
	return 0;
}

float Gearbox::getRatio(int gear)
{
	if(gear > m_gear_count || gear < 0)
		return 0;
		
	return m_gear_ratios[gear];
}

int Gearbox::getNeutralGear()
{
	return m_neutral_gear;
}

int Gearbox::getGearCount()
{
	return m_gear_count;
}

float Gearbox::getDifferentialRatio()
{
	return m_differential_ratio;
}

float Gearbox::getEfficiency()
{
	return m_efficiency;
}

float Gearbox::getDriveshaftInertia()
{
	return m_driveshaft_inertia;
}

std::ostream & operator <<(std::ostream & stream, Gearbox & gearbox)
{
	stream
	<<  "    --- Drivetrain ---    \n"
	<<  "Name: " << gearbox.m_name << "\n"
	<<  "Gears: " << gearbox.m_gear_count << "\n"
	<<  "Efficiency: " << (gearbox.m_efficiency * 100.0f) << "%\n"
	<<  "Differential ratio: " << gearbox.m_differential_ratio << ":1\n"
	<<  "Driveshaft overall inertia: " << gearbox.m_driveshaft_inertia << "kgm^2\n";

	int j = 0;
	for(int i = 0; i < gearbox.m_gear_count; i++)
	{
		float ratio = gearbox.m_gear_ratios[i];

		stream << "Gear ";
		if(ratio < 0.0f)
			stream << REVERSE_CHAR;
		else if(ratio == 0.0f)
			stream << NEUTRAL_CHAR;
		else
			stream << ++j;
		
		stream << " ratio: " << ratio << ":1\n";
	}    
	return stream;
}

