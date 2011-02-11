#ifndef DIFFERENTIAL_HPP
#define DIFFERENTIAL_HPP

#include "partmodelimplementation.hpp"

#include <string>

class IniFile;
class Vehicle;

class Differential: public PartModelImplementation
{
	public:
		const std::string& getName();
		int getPrice();
		bool fitsInVehicle(const Vehicle& vehicle);
		
		Differential(IniFile& iniFile);
		
	private:
		std::string name;
		
};

#endif // DIFFERENTIAL_HPP

