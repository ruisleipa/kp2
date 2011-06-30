#ifndef CHARGER_HPP
#define CHARGER_HPP

#include "part.hpp"

#include <string>

class IniFile;
class Vehicle;

class Charger: public Part
{
	public:
		const std::string& getName() const;
		float getMaxSpeed() const;
		float getAirPerRevolution() const;
		float getGearRatio() const;
		int getPrice() const;
		
		virtual Charger* clone() const;
		
		Charger(IniFile& iniFile);
		
	private:
		std::string name;		
		int maxSpeed;
		float airPerRevolution;
		float gearRatio;
};

#endif // CHARGER_HPP

