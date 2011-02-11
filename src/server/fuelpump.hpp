#ifndef FUELPUMP_HPP
#define FUELPUMP_HPP

#include "partmodelimplementation.hpp"

#include <string>

class IniFile;
class Vehicle;

class FuelPump: public PartModelImplementation
{
	public:
		const std::string& getName();
		int getPrice();
		bool fitsInVehicle(const Vehicle& vehicle);
		
		FuelPump(IniFile& iniFile);
		
	private:
		std::string name;
		
};

#endif // FUELPUMP_HPP

