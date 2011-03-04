#ifndef TIRE_HPP
#define TIRE_HPP

#include "partmodelimplementation.hpp"

#include <string>

class IniFile;
class Vehicle;

class Tire: public PartModelImplementation
{
	public:
		const std::string& getName() const;
		int getPrice() const;
		bool fitsInVehicle(const Vehicle& vehicle) const;
		
		Tire(IniFile& iniFile);
		
	private:
		std::string name;
		
};

#endif // TIRE_HPP

