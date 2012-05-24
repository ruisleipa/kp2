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
		float getEfficiency() const;
		std::vector<float> getGearRatios() const;
		
		Transmission(const Json::Value&);
		virtual void save(Json::Value&) const;
	
	private:
		float efficiency;
		std::vector<float> gears;
		
};

};

#endif // TRANSMISSION_HPP

