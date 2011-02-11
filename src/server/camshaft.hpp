#ifndef CAMSHAFT_HPP
#define CAMSHAFT_HPP

#include "partmodelimplementation.hpp"

#include <string>

class IniFile;
class Vehicle;

class Camshaft: public PartModelImplementation
{
	public:
		const std::string& getName();
		int getPrice();
		bool fitsInVehicle(const Vehicle& vehicle);
		
		Camshaft(IniFile& iniFile);
		
	private:
		std::string name;
		std::string camshaftPosition;
		std::string cylinderAlignment;		
		int cylinders;
};

#endif // CAMSHAFT_HPP

