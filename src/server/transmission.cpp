#include "transmission.hpp"

#include "utils/inifile.hpp"

std::vector<float> Transmission::getGearRatios() const
{
	return gears;
}

int Transmission::getNeutralGearIndex() const
{
	return neutralGear;
}

Transmission::Transmission(IniFile& iniFile):
	PartModel(iniFile)
{
	iniFile.getValue("neutralGear", neutralGear);
	
	int gearCount;
	
	iniFile.getValue("gearCount", gearCount);
	
	for(int i = 0; i < gearCount; i++)
	{
		float value;
		
		std::stringstream key;
		
		key << "gear[" << i << "]";
		
		iniFile.getValue(key.str(), value);
		
		gears.push_back(value);
	}
}
