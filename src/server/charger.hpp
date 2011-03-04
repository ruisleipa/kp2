#ifndef CHARGER_HPP
#define CHARGER_HPP

#include "partmodelimplementation.hpp"

#include <string>

class IniFile;
class Vehicle;

class Charger: public PartModelImplementation
{
	public:
		const std::string& getName() const;
		int getPrice() const;
		bool fitsInVehicle(const Vehicle& vehicle) const;
		
		Charger(IniFile& iniFile);
		
	private:
		std::string name;
		
		int size;
		float efficiency;
		std::string type;
};

#endif // CHARGER_HPP

