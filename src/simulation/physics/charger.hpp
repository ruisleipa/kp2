#ifndef PHYSICS_CHARGER_HPP
#define PHYSICS_CHARGER_HPP

#include "pipe.hpp"

namespace Physics
{

class Charger : public Pipe
{
	public:	
		virtual Air getAir(float maxVolume);
		
		float getPressure();
		
		void calculateSpeed(float engineSpeedInRpm);
		
		Charger(Pipe& pipe, float gearRatio, float airPerRevolution, float maxSpeed);

	private:
		float speedInRpm;
		
		float gearRatio;
		float airPerRevolution;
		float maxSpeed;
		
		Curve efficiencyCurve;
		
		float currentPressure;
		
};

};

#endif
