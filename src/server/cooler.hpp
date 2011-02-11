#ifndef COOLER_HPP
#define COOLER_HPP

#include "partmodelimplementation.hpp"

#include <string>

class IniFile;
class Vehicle;

class Cooler: public PartModelImplementation
{
	public:
		const std::string& getName();
		int getPrice();
		bool fitsInVehicle(const Vehicle& vehicle);
		
		Cooler(IniFile& iniFile);
		
	private:
		std::string name;
		
};

#endif // COOLER_HPP

