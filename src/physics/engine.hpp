#ifndef PHYSICS_ENGINE_HPP
#define PHYSICS_ENGINE_HPP

#include "units.hpp"

namespace Physics
{

class Engine
{
	public:
		class CylinderGeometry
		{
			public:
				Meters bore;
				Meters stroke;
				CubicMeters compressionVolume;
		};

		double getTorque();

		Engine(int cylinderCount, CylinderGeometry cylinderGeometry);

	private:
		int cylinderCount;
		CylinderGeometry cylinderGeometry;
};

}

#endif
