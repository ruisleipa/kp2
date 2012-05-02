#ifndef TRANSMISSION_HPP
#define TRANSMISSION_HPP

#include "part.hpp"

#include <string>
#include <vector>

namespace Game
{

class Transmission: public Part
{
	public:
		std::vector<float> getGearRatios() const;
		int getNeutralGearIndex() const;
		
		Transmission(const Json::Value&);
		virtual void save(Json::Value&) const;
	
	private:
		int neutralGear;
		std::vector<float> gears;
		
};

};

#endif // TRANSMISSION_HPP

