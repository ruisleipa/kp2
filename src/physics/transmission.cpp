#include "transmission.hpp"
#include <stdexcept>

namespace Physics
{

float Transmission::getInertia()
{
	return 0.01;
}

float Transmission::getRatio()
{
	return ratios[currentIndex];
}

float Transmission::getEfficiency()
{
	return efficiency;
}

Transmission::GearIndex Transmission::getLastGearIndex()
{
	return ratios.size() - 1;
}

void Transmission::setCurrentGear(Transmission::GearIndex gear)
{
	if(gear > getLastGearIndex())
		currentIndex = getLastGearIndex();
	else
		currentIndex = gear;
}

Transmission::GearIndex Transmission::getCurrentGear()
{
	return currentIndex;
}

Transmission::Transmission(const Game::Transmission& transmission):
	efficiency(transmission.getEfficiency()),
	ratios(transmission.getGearRatios()),
	currentIndex(decideInitialGear())
{
	if(ratios.size() == 0)
		throw std::range_error("transmission must have at least one gear");
}

Transmission::GearIndex Transmission::decideInitialGear()
{
	for(auto i = ratios.begin(); i != ratios.end(); ++i)
	{
		if(*i == 0.0)
			return std::distance(ratios.begin(), i);
	}

	return 0;
}

};
