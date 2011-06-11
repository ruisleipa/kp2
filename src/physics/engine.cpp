#include "engine.hpp"
#include "math_tools.hpp"
#include <cmath>
#include <iostream>

namespace Physics
{

Air Engine::getAir(float maxVolume)
{
	intakeAir = getIntake().getAir(calculateTheoreticalMixtureVolume() - exhaustLeft.getVolume());
	
	exhaustLeft = intakeAir;

	exhaust = exhaustLeft;
	exhaust.restrict(maxVolume);

	exhaustLeft.restrict(exhaustLeft.getVolume() - exhaust.getVolume());
	
	return exhaust;
}

void Engine::setSpeed(float speedInRpm)
{
	this->speedInRpm = speedInRpm;
}

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

float Engine::getTorque()
{
	float speedInRads = speedInRpm * RPM_TO_RADS;

	float trq = 0.0;
	float throttle = this->throttle;
	
	if ((speedInRpm <= idleRpm) && (throttle < idleThrottle))
		throttle = idleThrottle;
		
	//std::cout << throttle << " " << idleRpm << " " << idleThrottle << " " << speedInRpm << " " << ignition << std::endl;

	if(ignition)
	{
		if(dabs(speedInRads) < 1.0)
			trq += startEngineEffect;
		else
			trq += startEngineEffect / fabs(speedInRads);
	}

	if(rpmLimit == 0 || (speedInRpm < rpmLimit))
	{
		float theoreticalMixtureMass = calculateTheoreticalMixtureVolume() * 1.22521 / 1000.0;
		float freshMixtureMass = intakeAir.getMass();
		
		if(freshMixtureMass != 0 && theoreticalMixtureMass != 0)
		{		
			float intakeRatio = freshMixtureMass / theoreticalMixtureMass;
			
			float curveValue = torqueCurve.getValue(speedInRpm);
			
			
			
			if(curveValue != curveValue)
				curveValue = 0;
				
			//std::cout << curveValue << std::endl;
			
			
			trq += torqueCurve.getValue(speedInRpm) * intakeRatio * throttle;
		}
	}
		
	trq -= 0.07 * speedInRads * (1.0 - throttle);

	return trq;
}

float Engine::calculateTheoreticalMixtureVolume()
{
	return volume * cylinderCount / 2.0 * speedInRpm;
}

float Engine::calculateMaxFromIntakeManifold()
{
	return intakeAir.getVolume();
}

float Engine::calculateMaxToExhaustManifold()
{
	return exhaust.getVolume();
}

float Engine::calculateFreshMixtureInCylinder()
{
	return exhaust.getVolume();
}

float Engine::calculateExhaustLeftInCylinder()
{
	return exhaustLeft.getVolume();
}

float Engine::getFlywheelInertia()
{
	return flywheelInertia;
}

Engine::Engine(const Curve& torqueCurve, float volume, int cylinderCount,
	Pipe& intakePipe, float idleRpm, float idleThrottle, int rpmLimit,
	float startEngineEffect, float flywheelInertia
	):
	Pipe(intakePipe, 0),
	intakeAir(0, 0, 0),
	exhaustLeft(0, 0, 0),
	exhaust(0, 0, 0),
	speedInRpm(0),
	torqueCurve(torqueCurve),
	volume(volume),
	cylinderCount(cylinderCount),
	idleRpm(idleRpm),
	idleThrottle(idleThrottle),
	rpmLimit(rpmLimit),
	startEngineEffect(startEngineEffect),
	flywheelInertia(flywheelInertia),
	throttle(0.0),
	ignition(false)
{

}

};
