#ifndef INJECTOR_HPP
#define INJECTOR_HPP

#include "partmodel.hpp"

#include <string>

class IniFile;
class Vehicle;

class Injector: public PartModel
{
	public:
		const std::string& getName() const;
		int getPrice() const;
		
		Injector(IniFile& iniFile);
		
	private:
		std::string name;
		
};

#endif // INJECTOR_HPP

