#ifndef TIRE_HPP
#define TIRE_HPP

#include "partmodel.hpp"

#include <string>

class IniFile;
class Vehicle;

class Tire: public PartModel
{
	public:
		float getFrictionCoefficient() const;
		float getRollingResistanceCoefficient() const;
		float getRadius() const;
		
		Tire(IniFile& iniFile);
		
	private:
		float frictionCoefficient;
		float rollingResistanceCoefficient;
		float radius;
		
};

#endif // TIRE_HPP

