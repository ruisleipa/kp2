#include "engine.hpp"
#include "math_tools.hpp"
#include <cmath>

float Engine::getThrottle()
{
	return throttle;
}

void Engine::setThrottle(float throttle)
{
	this->throttle = throttle;
}

bool Engine::getIgnition()
{
	return ignition;
}

void Engine::setIgnition(bool ignition)
{
	this->ignition = ignition;
}

float Engine::getTorque(float speedInRads)
{
	int speedInRpm = speedInRads * RADS_TO_RPM;
	float trq = 0.0;

	if ((speedInRads <= idleSpeed) && (throttle < idleThrottle))
		throttle = idleThrottle;

	if(ignition)
	{
		if(dabs(speedInRads) < 1.0)
			trq += startEngineEffect;
		else
			trq += startEngineEffect / fabs(speedInRads);
	}

	if(rpmLimit == 0 || (speedInRpm < rpmLimit))
	{
		std::map<int, float>::iterator previous = torqueCurve.begin();
		std::map<int, float>::iterator current = torqueCurve.begin();
		
		while(current != torqueCurve.end() && current->first <= speedInRpm)
		{
			previous = current;
			
			++current;
		}
		
		if(current == torqueCurve.end())
		{
			current = previous;
		}
		
		int lowRpm = previous->first;
		int highRpm = current->first;
		float lowTorque = previous->second;
		float highTorque = current->second;
		
		float amount;
		
		if(lowRpm != speedInRpm)
			amount = float(speedInRpm - lowRpm) / float(highRpm - lowRpm);
		else
			amount = 0.0;
		
		float torque = lowTorque + ((highTorque - lowTorque) * amount);

		trq += torque * throttle;
	}

	return trq;
}

float Engine::getFlywheelInertia()
{
	return flywheelInertia;	
}

Engine::Engine(const std::map<int, float>& torqueCurve,	float idleSpeed,
	float idleThrottle, int rpmLimit, float startEngineEffect,
	float flywheelInertia
	):
	torqueCurve(torqueCurve),
	idleSpeed(idleSpeed),
	idleThrottle(idleThrottle),
	rpmLimit(rpmLimit),
	startEngineEffect(startEngineEffect),
	flywheelInertia(flywheelInertia),
	throttle(0.0),
	ignition(false)
{	

}
