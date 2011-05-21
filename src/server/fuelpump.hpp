#ifndef FUELPUMP_HPP
#define FUELPUMP_HPP

#include "partmodel.hpp"

#include <string>

class IniFile;
class Vehicle;

class FuelPump: public PartModel
{
	public:
		const std::string& getName() const;
		int getPrice() const;
		
		FuelPump(IniFile& iniFile);
		
	private:
		std::string name;
		
};

#endif // FUELPUMP_HPP

