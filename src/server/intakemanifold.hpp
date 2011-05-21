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
		
		void checkPrerequisiteParts(const Vehicle& vehicle) const;
		void checkForExtraPartsOfThisType(const Vehicle& vehicle) const;
		
		IntakeManifold(IniFile& iniFile);
		
	private:
		std::string name;
		std::string camshaftPosition;
		std::string cylinderAlignment;
		int cylinders;
		
};

#endif // INTAKEMANIFOLD_HPP

