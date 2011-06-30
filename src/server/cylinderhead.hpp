#ifndef CYLINDERHEAD_HPP
#define CYLINDERHEAD_HPP

#include "part.hpp"

#include <string>

class IniFile;
class Vehicle;

class CylinderHead: public Part
{
	public:
		const std::string& getName() const;
		int getPrice() const;
		const std::string& getCamshaftPosition() const;	
		const std::string& getCylinderAlignment() const;	
		int getCylinderCount() const;
		bool isDoubleCam() const;
		
		void checkPrerequisiteParts(const Vehicle& vehicle) const;
		void checkForExtraPartsOfThisType(const Vehicle& vehicle) const;
		
		virtual CylinderHead* clone() const;
		
		CylinderHead(IniFile& iniFile);
		
	private:
		std::string name;
		int doubleCam;
		std::string camshaftPosition;
		std::string cylinderAlignment;
		int cylinders;
};

#endif // CYLINDERHEAD_HPP

