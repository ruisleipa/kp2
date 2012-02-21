#ifndef PHYSICS_PIPE_HPP
#define PHYSICS_PIPE_HPP

#include "utils/curve.hpp"

#include "air.hpp"

namespace Physics
{

class Pipe
{
	public:
		virtual Air getAir(float maxVolume);
		
		Pipe(Pipe& intake, float maxVolume);

	protected:
		Pipe& getIntake();
	
	private:
		
		
		Pipe* intake;
		float maxVolume;
		
		Curve flowCurve;
	
};

};

#endif
