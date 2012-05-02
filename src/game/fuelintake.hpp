#ifndef FUELINTAKE_HPP
#define FUELINTAKE_HPP

#include "part.hpp"

namespace Game
{

class FuelIntake: public Part
{
	public:		
		FuelIntake(const Json::Value& value);
		virtual void save(Json::Value& value) const;
		
	private:
		
};

};

#endif

