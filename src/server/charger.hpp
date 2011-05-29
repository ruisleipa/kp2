#ifndef CHARGER_HPP
#define CHARGER_HPP

#include "partmodel.hpp"

#include <string>

class IniFile;
class Vehicle;

class Charger: public PartModel
{
	public:
		const std::string& getName() const;
		float getMaxSpeed() const;
		float getAirPerRevolution() const;
		float getGearRatio() const;
		int getPrice() const;
		
		Charger(IniFile& iniFile);
		
	private:
		std::string name;		
		int maxSpeed;
		float airPerRevolution;
		float gearRatio;
};

#endif // CHARGER_HPP

