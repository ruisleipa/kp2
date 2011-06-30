#ifndef FUELINTAKE_HPP
#define FUELINTAKE_HPP

#include "part.hpp"

#include <string>

class IniFile;
class Vehicle;

class FuelIntake: public Part
{
	public:
		const std::string& getName() const;
		int getPrice() const;
		
		virtual FuelIntake* clone() const;
		
		FuelIntake(IniFile& iniFile);
		
	private:
		std::string name;
		
};

#endif // FUELINTAKE_HPP

