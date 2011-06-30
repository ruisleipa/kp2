#ifndef TRANSMISSION_HPP
#define TRANSMISSION_HPP

#include "part.hpp"

#include <string>
#include <vector>

class IniFile;
class Vehicle;

class Transmission: public Part
{
	public:
		std::vector<float> getGearRatios() const;
		int getNeutralGearIndex() const;
		
		virtual Transmission* clone() const;
		
		Transmission(IniFile& iniFile);
		
	private:
		int neutralGear;
		std::vector<float> gears;
		
};

#endif // TRANSMISSION_HPP

