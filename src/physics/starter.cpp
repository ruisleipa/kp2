#include "starter.hpp"
#include "math_tools.hpp"

namespace Physics
{

float Starter::getTorque(float speed)
{
	if(running && speed < 1000 * RPM_TO_RADS)
		return 10.0;

	return 0.0;
}

float Starter::getInertia()
{
	//TODO: calculate real inertia
	return 0.1;
}

void Starter::setRunning(bool running)
{
	this->running = running;
}

Starter::Starter():
	running(false)
{

}

};
