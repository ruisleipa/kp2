#ifndef FUELPUMP_HPP
#define FUELPUMP_HPP

#include "partmodelimplementation.hpp"

#include <string>

class IniFile;
class Vehicle;

class FuelPump: public PartModelImplementation
{
	public:
		const std::string& getName() const;
		int getPrice() const;
		bool fitsInVehicle(const Vehicle& vehicle) const;
		
		FuelPump(IniFile& iniFile);
		
	private:
		std::string name;
		
};

#endif // FUELPUMP_HPP

