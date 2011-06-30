#ifndef COOLER_HPP
#define COOLER_HPP

#include "part.hpp"

#include <string>

class IniFile;
class Vehicle;

class Cooler: public Part
{
	public:
		const std::string& getName() const;
		int getPrice() const;
		
		virtual Cooler* clone() const;
		
		Cooler(IniFile& iniFile);
		
	private:
		std::string name;
		
};

#endif // COOLER_HPP

