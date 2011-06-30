#ifndef TIRE_HPP
#define TIRE_HPP

#include "part.hpp"

#include <string>

class IniFile;
class Vehicle;

class Tire: public Part
{
	public:
		float getFrictionCoefficient() const;
		float getRollingResistanceCoefficient() const;
		float getRadius() const;
		
		virtual Tire* clone() const;
		
		Tire(IniFile& iniFile);
		
	private:
		float frictionCoefficient;
		float rollingResistanceCoefficient;
		float radius;
		
};

#endif // TIRE_HPP

