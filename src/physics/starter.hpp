#ifndef PHYSICS_STARTER_HPP
#define PHYSICS_STARTER_HPP

namespace Physics
{

class Starter
{
	public:
		float getTorque(float speed);
		float getInertia();

		void setRunning(bool running);

		Starter();

	private:
		bool running;
};

};

#endif
