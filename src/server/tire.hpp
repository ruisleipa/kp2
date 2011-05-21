#ifndef TIRE_HPP
#define TIRE_HPP

#include "partmodel.hpp"

#include <string>

class IniFile;
class Vehicle;

class Tire: public PartModel
{
	public:
		const std::string& getName() const;
		int getPrice() const;
		
		Tire(IniFile& iniFile);
		
	private:
		std::string name;
		
};

#endif // TIRE_HPP

