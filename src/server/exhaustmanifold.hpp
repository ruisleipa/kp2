#ifndef EXHAUSTMANIFOLD_HPP
#define EXHAUSTMANIFOLD_HPP

#include "partmodelimplementation.hpp"

#include <string>

class IniFile;
class Vehicle;

class ExhaustManifold: public PartModelImplementation
{
	public:
		const std::string& getName() const;
		int getPrice() const;
		bool fitsInVehicle(const Vehicle& vehicle) const;
		
		ExhaustManifold(IniFile& iniFile);
		
	private:
		std::string name;
		
};

#endif // EXHAUSTMANIFOLD_HPP

