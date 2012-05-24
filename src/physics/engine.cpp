#include "engine.hpp"
#include "math_tools.hpp"

namespace Physics
{

float Engine::getTorque(float speed)
{
	float speedInRpm = speed * RADS_TO_RPM;
	float speedInRads = speed;

	float throttle = this->throttle;

	float trq = 0.0;

	if ((speedInRpm <= idleRpm) && (throttle < idleThrottle))
		throttle = idleThrottle;

	if(rpmLimit == 0 || (speedInRpm < rpmLimit))
	{
		float curveValue = torqueCurve.getValue(speedInRpm);

		if(curveValue != curveValue)
			curveValue = 0;

		trq += curveValue * throttle;
	}

	trq += -0.05 * speedInRads;

	return trq;
}

float Engine::getInertia()
{
	//TODO: calculate real inertia
	return 0.1;
}

void Engine::setThrottle(float throttle)
{
	this->throttle = throttle;

	if(this->throttle > 1.0)
		this->throttle = 1.0;

	if(this->throttle < 0.0)
		this->throttle = 0.0;
}

Engine::Engine(Game::Engine& engine):
	torqueCurve(engine.getTorqueCurve()),
	volume(engine.getVolume()),
	cylinderCount(engine.getCylinderCount()),
	idleRpm(engine.getIdleSpeed()),
	idleThrottle(1),
	rpmLimit(engine.getSpeedLimit()),
	throttle(0.0)
{

}

};
