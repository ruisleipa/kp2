#ifndef CHARGER_HPP
#define CHARGER_HPP

#include "partmodel.hpp"

#include <string>

class IniFile;
class Vehicle;

class Charger: public PartModel
{
	public:
		const std::string& getName() const;
		int getPrice() const;
		
		Charger(IniFile& iniFile);
		
	private:
		std::string name;
		
		int size;
		float efficiency;
		std::string type;
};

#endif // CHARGER_HPP

