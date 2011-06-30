#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "part.hpp"
#include "utils/curve.hpp"

#include <string>

class IniFile;
class Vehicle;

class Engine: public Part
{
	public:	
		const std::string& getName() const;
		int getPrice() const;
		const std::string& getCamshaftPosition() const;	
		const std::string& getCylinderAlignment() const;	
		int getCylinderCount() const;	
		const Curve& getTorqueCurve() const;
		int getIdleSpeed() const;
		int getSpeedLimit() const;
		
		void checkPrerequisiteParts(const Vehicle& vehicle) const;
		void checkForExtraPartsOfThisType(const Vehicle& vehicle) const;
		
		virtual Engine* clone() const;
		
		Engine(IniFile& partFile);
		
	private:
		std::string camshaftPosition;
		std::string cylinderAlignment;
		int cylinders;
		
		float compression;
		float volume;	

		std::string name;
		
		Curve torqueCurve;
};

#endif // ENGINE_HPP

