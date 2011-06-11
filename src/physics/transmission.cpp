#include "transmission.hpp"
#include <stdexcept>

namespace Physics
{

Transmission::Transmission(std::vector<float> ratios, size_t neutralIndex,
	float efficiency, float differentialRatio, float driveshaftInertia
	):
	differentialRatio(differentialRatio),
	efficiency(efficiency),
	driveshaftInertia(driveshaftInertia),
	ratios(ratios),
	neutralIndex(neutralIndex),
	currentIndex(neutralIndex)
{
	if(ratios.size() == 0)
		throw std::range_error("transmission must have at least one gear");

	if(neutralIndex >= ratios.size())
		throw std::range_error("index of neutral gear out of range");
}

float Transmission::getRatio()
{
	if(isOnNeutral())
		return 0.0;
	
	return ratios[currentIndex];
}

bool Transmission::isOnNeutral()
{
	return currentIndex == neutralIndex;
}

void Transmission::lowerGear()
{
	if(currentIndex > 0)
		currentIndex--;
}

void Transmission::upperGear()
{
	if(currentIndex != ratios.size() - 1)
		currentIndex++;
}

float Transmission::getEfficiency()
{
	return efficiency;
}

float Transmission::getDifferentialRatio()
{
	return differentialRatio;
}

float Transmission::getDriveshaftInertia()
{
	return driveshaftInertia;
}

};
