#ifndef DIFFERENTIAL_HPP
#define DIFFERENTIAL_HPP

#include "partmodel.hpp"

#include <string>

class IniFile;
class Vehicle;

class Differential: public PartModel
{
	public:
		const std::string& getName() const;
		int getPrice() const;
		
		Differential(IniFile& iniFile);
		
	private:
		std::string name;
		
};

#endif // DIFFERENTIAL_HPP

