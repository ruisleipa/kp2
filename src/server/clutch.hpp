#ifndef CLUTCH_HPP
#define CLUTCH_HPP

#include "partmodelimplementation.hpp"

#include <string>

class IniFile;
class Vehicle;

class Clutch: public PartModelImplementation
{
	public:
		const std::string& getName();
		int getPrice();
		bool fitsInVehicle(const Vehicle& vehicle);
		
		Clutch(IniFile& iniFile);
		
	private:
		std::string name;
		
};

#endif // CLUTCH_HPP

