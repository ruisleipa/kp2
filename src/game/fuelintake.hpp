#ifndef FUELINTAKE_HPP
#define FUELINTAKE_HPP

#include "part.hpp"

namespace Game
{

class FuelIntake: public Part
{
	public:
		virtual FuelIntake* clone() const;
		
		FuelIntake(const Json::Value& value);
		void save(Json::Value& value);
		
	private:
		
};

};

#endif

