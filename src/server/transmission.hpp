#ifndef TRANSMISSION_HPP
#define TRANSMISSION_HPP

#include "partmodelimplementation.hpp"

#include <string>

class IniFile;
class Vehicle;

class Transmission: public PartModelImplementation
{
	public:
		const std::string& getName() const;
		int getPrice() const;
		
		Transmission(IniFile& iniFile);
		
	private:
		std::string name;
		
};

#endif // TRANSMISSION_HPP

