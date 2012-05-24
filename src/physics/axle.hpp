#ifndef PHYSICS_AXLE_HPP
#define PHYSICS_AXLE_HPP

namespace Physics
{

class Axle
{
	public:
		float getInertia();

		Axle(float inertia);

	private:
		float inertia;
};

};

#endif
