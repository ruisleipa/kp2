#ifndef INJECTOR_HPP
#define INJECTOR_HPP

#include "partmodelimplementation.hpp"

#include <string>

class IniFile;
class Vehicle;

class Injector: public PartModelImplementation
{
	public:
		const std::string& getName() const;
		int getPrice() const;
		bool fitsInVehicle(const Vehicle& vehicle) const;
		
		Injector(IniFile& iniFile);
		
	private:
		std::string name;
		
};

#endif // INJECTOR_HPP

