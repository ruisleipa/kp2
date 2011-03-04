#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "partmodelimplementation.hpp"

#include <string>

class IniFile;
class Vehicle;

class Engine: public PartModelImplementation
{
	public:	
		const std::string& getName() const;
		int getPrice() const;
		const std::string& getCamshaftPosition() const;	
		const std::string& getCylinderAlignment() const;	
		int getCylinderCount() const;	
		bool fitsInVehicle(const Vehicle& vehicle) const;
		
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

