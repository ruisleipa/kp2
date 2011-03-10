#ifndef CLUTCH_HPP
#define CLUTCH_HPP

#include "partmodelimplementation.hpp"

#include <string>

class IniFile;
class Vehicle;

class Clutch: public PartModelImplementation
{
	public:
		const std::string& getName() const;
		int getPrice() const;
		
		Clutch(IniFile& iniFile);
		
	private:
		std::string name;
		
};

#endif // CLUTCH_HPP

