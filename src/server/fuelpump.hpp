#ifndef FUELPUMP_HPP
#define FUELPUMP_HPP

#include "part.hpp"

#include <string>

class IniFile;
class Vehicle;

class FuelPump: public Part
{
	public:
		const std::string& getName() const;
		int getPrice() const;
		
		virtual FuelPump* clone() const;
		
		FuelPump(IniFile& iniFile);
		
	private:
		std::string name;
		
};

#endif // FUELPUMP_HPP

