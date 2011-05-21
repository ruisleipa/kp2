#ifndef CAMSHAFT_HPP
#define CAMSHAFT_HPP

#include "partmodel.hpp"

#include <string>

class IniFile;
class Vehicle;

class Camshaft: public PartModel
{
	public:
		const std::string& getName() const;
		int getPrice() const;
		
		void checkPrerequisiteParts(const Vehicle& vehicle) const;
		void checkForExtraPartsOfThisType(const Vehicle& vehicle) const;
	
		Camshaft(IniFile& iniFile);
		
	private:
		std::string name;
		std::string camshaftPosition;
		int cylinders;
};

#endif // CAMSHAFT_HPP

