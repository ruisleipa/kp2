#ifndef PHYSICS_ENGINE_HPP
#define PHYSICS_ENGINE_HPP

#include "game/engine.hpp"
#include "utils/curve.hpp"

namespace Physics
{

class Engine
{
	public:
		float getTorque(float speed);
		float getInertia();

		void setThrottle(float throttle);

		Engine(Game::Engine& engine);

	private:
		Curve torqueCurve;
		float volume;
		int cylinderCount;
		float idleRpm;
		float idleThrottle;
		int rpmLimit;

		float throttle;
};

};

#endif
