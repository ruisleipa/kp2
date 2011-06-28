#ifndef EXHAUSTMANIFOLD_HPP
#define EXHAUSTMANIFOLD_HPP

#include "partmodel.hpp"

#include <string>

class IniFile;
class Vehicle;

class ExhaustManifold: public PartModel
{
	public:
		float getFlow() const;
		
		void checkPrerequisiteParts(const Vehicle& vehicle) const;
		void checkForExtraPartsOfThisType(const Vehicle& vehicle) const;
		
		ExhaustManifold(IniFile& iniFile);
		
	private:
		std::string name;
		std::string camshaftPosition;
		std::string cylinderAlignment;
		int cylinders;
		
		float flow;		
};

#endif // EXHAUSTMANIFOLD_HPP

