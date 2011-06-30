#ifndef DIFFERENTIAL_HPP
#define DIFFERENTIAL_HPP

#include "part.hpp"

#include <string>

class IniFile;
class Vehicle;

class Differential: public Part
{
	public:
		const std::string& getName() const;
		int getPrice() const;
		
		virtual Differential* clone() const;
		
		Differential(IniFile& iniFile);
		
	private:
		std::string name;
		
};

#endif // DIFFERENTIAL_HPP

