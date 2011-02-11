#ifndef CYLINDERHEAD_HPP
#define CYLINDERHEAD_HPP

#include "partmodelimplementation.hpp"

#include <string>

class IniFile;
class Vehicle;

class CylinderHead: public PartModelImplementation
{
	public:
		const std::string& getName();
		int getPrice();
		bool fitsInVehicle(const Vehicle& vehicle);
		
		CylinderHead(IniFile& iniFile);
		
	private:
		std::string name;
		int doubleCam;
		std::string camshaftPosition;
		std::string cylinderAlignment;		
		int cylinders;
};

#endif // CYLINDERHEAD_HPP

