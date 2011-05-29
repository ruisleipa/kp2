#include "pipe.hpp"

#include <algorithm>

namespace Physics
{

Air Pipe::getAir(float maxVolume)
{	
	float ratio = maxVolume / this->maxVolume;
	
	float flowRatio = flowCurve.getValue(ratio * 100.0);
	
	Air air = intake->getAir(this->maxVolume * flowRatio);
	
	air.restrict(maxVolume);
	
	return air;
}

Pipe& Pipe::getIntake()
{
	return *intake;
}

Pipe::Pipe(Pipe& intake, float maxVolume):
	intake(&intake),
	maxVolume(maxVolume)
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
