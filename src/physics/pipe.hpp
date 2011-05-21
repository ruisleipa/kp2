#ifndef PHYSICS_PIPE_HPP
#define PHYSICS_PIPE_HPP

#include "utils/curve.hpp"

namespace Physics
{

class Pipe
{
	public:
		float getFlow(float needed) const;
		
		Pipe(float maxFlow);

	private:
		float maxFlow;
		
		Curve flowCurve;
	
};

};

#endif
