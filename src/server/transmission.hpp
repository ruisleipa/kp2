#ifndef TRANSMISSION_HPP
#define TRANSMISSION_HPP

#include "partmodel.hpp"

#include <string>
#include <vector>

class IniFile;
class Vehicle;

class Transmission: public PartModel
{
	public:
		std::vector<float> getGearRatios() const;
		int getNeutralGearIndex() const;
		
		Transmission(IniFile& iniFile);
		
	private:
		int neutralGear;
		std::vector<float> gears;
		
};

#endif // TRANSMISSION_HPP

