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
		
		virtual Tire* clone() const;
		
		Tire(const Json::Value&);
		void save(Json::Value&);
		
	private:
		float frictionCoefficient;
		float rollingResistanceCoefficient;
		float radius;
		
};

};

#endif // TIRE_HPP

