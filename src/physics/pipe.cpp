#include "pipe.hpp"

#include <algorithm>

namespace Physics
{

float Pipe::getFlow(float needed) const
{
	float ratio = needed / maxFlow;	
	
	float flowRatio = flowCurve.getValue(ratio * 100.0);
		
	return std::min(needed, maxFlow * flowRatio);
}

Pipe::Pipe(float maxFlow):
	maxFlow(maxFlow)
{
	flowCurve.addPoint(0, 0.0);
	flowCurve.addPoint(80, 0.80);
	flowCurve.addPoint(90, 0.85);
	flowCurve.addPoint(100, 0.9);
	flowCurve.addPoint(110, 0.95);
	flowCurve.addPoint(120, 0.98);
	flowCurve.addPoint(150, 1.0);	
	flowCurve.addPoint(1000000000, 1.0);
}

};
