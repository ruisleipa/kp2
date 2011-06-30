#ifndef INJECTOR_HPP
#define INJECTOR_HPP

#include "part.hpp"

#include <string>

class IniFile;
class Vehicle;

class Injector: public Part
{
	public:
		const std::string& getName() const;
		int getPrice() const;
		
		virtual Injector* clone() const;
		
		Injector(IniFile& iniFile);
		
	private:
		std::string name;
		
};

#endif // INJECTOR_HPP

