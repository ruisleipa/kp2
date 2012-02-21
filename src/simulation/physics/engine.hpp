#ifndef _ENGINE_HPP
#define _ENGINE_HPP

#include "utils/curve.hpp"
#include "pipe.hpp"

namespace Physics
{

class Engine : public Pipe
{
	public:
		virtual Air getAir(float maxVolume);
		
		void setSpeed(float speedInRpm);
		
		float getThrottle();
		void setThrottle(float throttle);

		bool getIgnition();
		void setIgnition(bool ignition);
		
		float getTorque();
		float calculateTheoreticalMixtureVolume();
		
		float calculateMaxFromIntakeManifold();
		float calculateMaxToExhaustManifold();
		float calculateFreshMixtureInCylinder();
		float calculateExhaustLeftInCylinder();
		
		float getFlywheelInertia();
		
		Engine(const Curve& torqueCurve, float volume, int cylinderCount, Pipe& intakePipe, float idleRpm, float idleThrottle, int rpmLimit, float flywheelInertia, float startEngineEffect);

	private:
		Air intakeAir;
		Air exhaustLeft;
		Air exhaust;
		
		float speedInRpm;
		
		Curve torqueCurve;
		float volume;
		int cylinderCount;
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
