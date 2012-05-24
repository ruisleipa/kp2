#include "axle.hpp"

namespace Physics
{

float Axle::getInertia()
{
	return inertia;
}

Axle::Axle(float inertia):
	inertia(inertia)
{

}

};
