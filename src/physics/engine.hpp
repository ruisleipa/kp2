#ifndef _ENGINE_HPP
#define _ENGINE_HPP

#include <iostream>
#include <string>
#include <map>

class Engine
{
	public:
		float getThrottle();
		void setThrottle(float throttle);

		bool getIgnition();
		void setIgnition(bool ignition);
		
		float getTorque(float speedInRads);
		float getFlywheelInertia();
		
		Engine(const std::map<int, float>& torqueCurve, float idleRpm, float idleThrottle, int rpmLimit, float flywheelInertia, float startEngineEffect);

	private:
		std::map<int, float> torqueCurve;
		float idleRpm;
		float idleThrottle;
		int rpmLimit;
		float startEngineEffect;
		float flywheelInertia;
		
		float throttle;
		bool ignition;		
};


#endif
