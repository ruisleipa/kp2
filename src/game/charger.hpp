#ifndef CHARGER_HPP
#define CHARGER_HPP

#include "part.hpp"

#include <string>

namespace Game
{

class Vehicle;

class Charger: public Part
{
	public:
		int getPrice() const;
		
		Charger(const Json::Value& value);
		virtual void save(Json::Value& value);
		
	private:
		std::string name;		
		int maxSpeed;
		float airPerRevolution;
		float gearRatio;
};

};

#endif // CHARGER_HPP

