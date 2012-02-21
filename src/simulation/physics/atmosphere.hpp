#ifndef PHYSICS_ATMOSPHERE_HPP
#define PHYSICS_ATMOSPHERE_HPP

#include "utils/curve.hpp"

#include "pipe.hpp"

namespace Physics
{

class Atmosphere : public Pipe
{
	public:
		virtual Air getAir(float maxVolume);
		
		Atmosphere();
		
	private:
		Pipe nullPipe;
	
};

};

#endif
