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
	float throttle = this->throttle;

	if ((speedInRpm <= idleRpm) && (throttle < idleThrottle))
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
		float theoreticalMixtureUsage = calculateTheoreticalMixtureUsage(speedInRpm);		
		float freshMixtureInCylinder = calculateFreshMixtureInCylinder(speedInRpm);
		
		if(freshMixtureInCylinder != 0 && theoreticalMixtureUsage != 0)
		{		
			float intakeRatio = freshMixtureInCylinder / theoreticalMixtureUsage;
			
			trq += torqueCurve.getValue(speedInRpm) * intakeRatio;
		}
	}
		
	trq -= 0.07 * speedInRads * (1.0 - throttle);

	return trq;
}

float Engine::calculateTheoreticalMixtureUsage(float speedInRpm)
{
	return volume * cylinderCount / 2.0 * speedInRpm;
}

float Engine::calculateMaxFromIntakeManifold(float speedInRpm)
{
	return intakePipe.getFlow(calculateTheoreticalMixtureUsage(speedInRpm)) * throttle;
}

float Engine::calculateMaxToExhaustManifold(float speedInRpm)
{
	return exhaustPipe.getFlow(calculateMaxFromIntakeManifold(speedInRpm));
}

float Engine::calculateFreshMixtureInCylinder(float speedInRpm)
{
	return calculateMaxFromIntakeManifold(speedInRpm) - calculateExhaustLeftInCylinder(speedInRpm);
}

float Engine::calculateExhaustLeftInCylinder(float speedInRpm)
{	
	return calculateMaxFromIntakeManifold(speedInRpm) - calculateMaxToExhaustManifold(speedInRpm);
}

float Engine::getFlywheelInertia()
{
	return flywheelInertia;	
}

Engine::Engine(const Curve& torqueCurve, float volume, int cylinderCount,
	const Pipe& intakePipe, const Pipe& exhaustPipe, float idleRpm, 
	float idleThrottle, int rpmLimit, float startEngineEffect,
	float flywheelInertia
	):
	torqueCurve(torqueCurve),
	volume(volume),
	cylinderCount(cylinderCount),
	intakePipe(intakePipe),
	exhaustPipe(exhaustPipe),
	idleRpm(idleRpm),
	idleThrottle(idleThrottle),
	rpmLimit(rpmLimit),
	startEngineEffect(startEngineEffect),
	flywheelInertia(flywheelInertia),
	throttle(0.0),
	ignition(false)
{	

}
