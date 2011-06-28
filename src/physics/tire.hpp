#ifndef _TIRE_HPP
#define _TIRE_HPP

namespace Physics
{

class Tire
{
	public:
		Tire(float mass, float radius, float rollingResistanceCoefficient, float frictionCoefficient);
		
		double getFriction(double load);
		double getRadius();
		double getInertia();
		double getRollingResistance(double load,double speed);
	
		double setSlipRatio(double slipRatio);
		
	private:
		double slipRatio;
		double radius;
		double inertia;
		double rollingResistanceCoefficient;
		double frictionCoefficient;
};

};

#endif
