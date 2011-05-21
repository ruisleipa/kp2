#ifndef CLUTCH_HPP
#define CLUTCH_HPP

#include "partmodel.hpp"

#include <string>

class IniFile;
class Vehicle;

class Clutch: public PartModel
{
	public:
		const std::string& getName() const;
		int getPrice() const;
		
		Clutch(IniFile& iniFile);
		
	private:
		std::string name;
		
};

#endif // CLUTCH_HPP

