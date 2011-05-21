#ifndef FUELINTAKE_HPP
#define FUELINTAKE_HPP

#include "partmodel.hpp"

#include <string>

class IniFile;
class Vehicle;

class FuelIntake: public PartModel
{
	public:
		const std::string& getName() const;
		int getPrice() const;
		
		FuelIntake(IniFile& iniFile);
		
	private:
		std::string name;
		
};

#endif // FUELINTAKE_HPP

