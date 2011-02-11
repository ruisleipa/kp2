#ifndef TRANSMISSION_HPP
#define TRANSMISSION_HPP

#include "partmodelimplementation.hpp"

#include <string>

class IniFile;
class Vehicle;

class Transmission: public PartModelImplementation
{
	public:
		const std::string& getName();
		int getPrice();
		bool fitsInVehicle(const Vehicle& vehicle);
		
		Transmission(IniFile& iniFile);
		
	private:
		std::string name;
		
};

#endif // TRANSMISSION_HPP

