#ifndef CLUTCH_HPP
#define CLUTCH_HPP

#include "part.hpp"

#include <string>

class IniFile;
class Vehicle;

class Clutch: public Part
{
	public:
		const std::string& getName() const;
		int getPrice() const;
		
		virtual Clutch* clone() const;
		
		Clutch(IniFile& iniFile);
		
	private:
		std::string name;
		
};

#endif // CLUTCH_HPP

