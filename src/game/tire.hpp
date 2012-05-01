#ifndef TIRE_HPP
#define TIRE_HPP

#include "part.hpp"

#include <string>

namespace Game
{

class Tire: public Part
{
	public:
		float getFrictionCoefficient() const;
		float getRollingResistanceCoefficient() const;
		float getRadius() const;
		
		Tire(const Json::Value&);
		virtual void save(Json::Value& value) const;
		
	private:
		float frictionCoefficient;
		float rollingResistanceCoefficient;
		float radius;
		
};

};

#endif // TIRE_HPP

