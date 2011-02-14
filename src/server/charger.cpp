#include "charger.hpp"

#include "utils/inifile.hpp"
#include "vehicle.hpp"

const std::string& Charger::getName()
{
	return name;
}

int Charger::getPrice()
{
	return 150;
}

bool Charger::fitsInVehicle(const Vehicle& vehicle)
{
	return true;
}

Charger::Charger(IniFile& iniFile)
{
	iniFile.getValue("size",size);
	iniFile.getValue("efficiency",efficiency);
	iniFile.getValue("chargerType",type);

	efficiency /= 100.0;
	
	std::stringstream ss;
	
	switch(size)
	{
		case 1:
			ss << "Small";
			break;
		case 2:
			ss << "Medium";
			break;
		case 3:
			ss << "Large";
			break;
	}
	
	ss << " ";
	ss << type;
	ss << "charger";
	
	name = ss.str();
}