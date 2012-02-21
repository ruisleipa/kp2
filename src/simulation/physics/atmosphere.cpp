#include "atmosphere.hpp"

#include <algorithm>

namespace Physics
{

Air Atmosphere::getAir(float maxVolume)
{			
	return Air(maxVolume / 1000.0 * 1.22521 , maxVolume, 273 + 15);
}

Atmosphere::Atmosphere():
	Pipe(nullPipe, 0),
	nullPipe(nullPipe, 0)
{

}

};
