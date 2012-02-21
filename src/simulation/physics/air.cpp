#include "air.hpp"

#include <cmath>

namespace Physics
{

float Air::getMass()
{
	return mass;
}

float Air::getVolume()
{
	return volume;
}

float Air::getTemperature()
{
	return temperatureInKelvin;
}

float Air::getPressure()
{
	const float gasConstant = 8.314472;
	const float airMolarMass = 28.97 / 1000.0;
	
	return ((mass / airMolarMass) * gasConstant * temperatureInKelvin) / (volume / 1000.0);
}

void Air::compress(float newVolume)
{
	if(newVolume == 0)
	{
		mass = 0;
		volume = 0;
		
		return;
	}
	
	// degrees of freedom divided by 2, 5/2 for diatomic gases
	float a = 5.0 / 2.0;

	// T2^a = T1^a * V1 / V2
	float newTemperature = pow(pow(temperatureInKelvin, a) * volume / newVolume, 1.0 / a);

	volume = newVolume;
	temperatureInKelvin = newTemperature;	
}

void Air::restrict(float newVolume)
{
	//TODO: how to correctly model air moving in pipes

	if(newVolume <= 0)
	{
		mass = 0;
		volume = 0;
		
		return;
	}
	
	if(newVolume > volume)
		return;
	
	mass *= newVolume / volume;

	volume = newVolume;
}

Air::Air(float mass, float volume, float temperatureInKelvin):
	mass(mass),
	volume(volume),
	temperatureInKelvin(temperatureInKelvin)
{

}

};
