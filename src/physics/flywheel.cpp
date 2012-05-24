#include "flywheel.hpp"

namespace Physics
{

float Flywheel::getTorque()
{
	return 0.0;
}

float Flywheel::getInertia()
{
	return inertia;
}

Flywheel::Flywheel():
	inertia(0.22) //TODO: calculate real inertia
{

}

};
