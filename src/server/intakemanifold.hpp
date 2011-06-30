#ifndef INTAKEMANIFOLD_HPP
#define INTAKEMANIFOLD_HPP

#include "part.hpp"

#include <string>

class IniFile;
class Vehicle;

class IntakeManifold: public Part
{
	public:
		const std::string& getName() const;
		int getPrice() const;
		float getFlow() const;
		
		void checkPrerequisiteParts(const Vehicle& vehicle) const;
		void checkForExtraPartsOfThisType(const Vehicle& vehicle) const;
		
		virtual IntakeManifold* clone() const;
		
		IntakeManifold(IniFile& iniFile);
		
	private:
		std::string name;
		std::string camshaftPosition;
		std::string cylinderAlignment;
		int cylinders;
		
		float flow;
		
};

#endif // INTAKEMANIFOLD_HPP

