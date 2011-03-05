#ifndef CYLINDERHEAD_HPP
#define CYLINDERHEAD_HPP

#include "partmodelimplementation.hpp"

#include <string>

class IniFile;
class Vehicle;

class CylinderHead: public PartModelImplementation
{
	public:
		const std::string& getName() const;
		int getPrice() const;
		const std::string& getCamshaftPosition() const;	
		int getCylinderCount() const;
		bool fitsInVehicle(const Vehicle& vehicle) const;
		
		CylinderHead(IniFile& iniFile);
		
	private:
		std::string name;
		int doubleCam;
		std::string camshaftPosition;
		int cylinders;
};

#endif // CYLINDERHEAD_HPP

