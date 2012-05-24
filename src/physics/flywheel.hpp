#ifndef PHYSICS_FLYWHEEL_HPP
#define PHYSICS_FLYWHEEL_HPP

namespace Physics
{

class Flywheel
{
	public:
		float getTorque();
		float getInertia();

		Flywheel();

	private:
		float inertia;

};

};

#endif
