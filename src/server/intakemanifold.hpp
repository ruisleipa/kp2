#ifndef INTAKEMANIFOLD_HPP
#define INTAKEMANIFOLD_HPP

#include "partmodel.hpp"

#include <string>

class IniFile;
class Vehicle;

class IntakeManifold: public PartModel
{
	public:
		const std::string& getName() const;
		int getPrice() const;
		
		IntakeManifold(IniFile& iniFile);
		
	private:
		std::string name;
		
};

#endif // INTAKEMANIFOLD_HPP

