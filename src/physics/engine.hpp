#ifndef _ENGINE_HPP
#define _ENGINE_HPP

#include "utils/curve.hpp"
#include "pipe.hpp"

namespace Physics
{

class Engine
{
	public:
		float getThrottle();
		void setThrottle(float throttle);

		bool getIgnition();
		void setIgnition(bool ignition);
		
		float getTorque(float speedInRads);
		float calculateTheoreticalMixtureUsage(float speedInRpm);
		float calculateMaxFromIntakeManifold(float speedInRpm);
		float calculateMaxToExhaustManifold(float speedInRpm);
		float calculateFreshMixtureInCylinder(float speedInRpm);
		float calculateExhaustLeftInCylinder(float speedInRpm);
		
		float getFlywheelInertia();
		
		Engine(const Curve& torqueCurve, float volume, int cylinderCount, const Pipe& intakePipe, const Pipe& exhaustPipe, float idleRpm, float idleThrottle, int rpmLimit, float flywheelInertia, float startEngineEffect);

	private:
		Curve torqueCurve;
		float volume;
		int cylinderCount;
		const Pipe& intakePipe;
		const Pipe& exhaustPipe;
		float idleRpm;
		float idleThrottle;
		int rpmLimit;
		float startEngineEffect;
		float flywheelInertia;
		
		float throttle;
		bool ignition;		
};

};

#endif
