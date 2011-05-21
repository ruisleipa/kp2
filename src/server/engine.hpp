#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "partmodel.hpp"

#include <string>

class IniFile;
class Vehicle;

class Engine: public PartModel
{
	public:	
		const std::string& getName() const;
		int getPrice() const;
		const std::string& getCamshaftPosition() const;	
		const std::string& getCylinderAlignment() const;	
		int getCylinderCount() const;	
		
		void checkPrerequisiteParts(const Vehicle& vehicle) const;
		void checkForExtraPartsOfThisType(const Vehicle& vehicle) const;
		
		Engine(IniFile& partFile);
		
	private:
		std::string camshaftPosition;
		std::string cylinderAlignment;
		int cylinders;
		
		float compression;
		float volume;	

		std::string name;
};

#endif // ENGINE_HPP

