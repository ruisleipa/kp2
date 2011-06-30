#ifndef CAMSHAFT_HPP
#define CAMSHAFT_HPP

#include "part.hpp"

#include <string>

class IniFile;
class Vehicle;

class Camshaft: public Part
{
	public:
		const std::string& getName() const;
		int getPrice() const;
		
		void checkPrerequisiteParts(const Vehicle& vehicle) const;
		void checkForExtraPartsOfThisType(const Vehicle& vehicle) const;
		
		virtual Camshaft* clone() const;
		
		Camshaft(IniFile& iniFile);
		
	private:
		std::string name;
		std::string camshaftPosition;
		int cylinders;
};

#endif // CAMSHAFT_HPP

