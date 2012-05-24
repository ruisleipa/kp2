#ifndef PHYSICS_TRANSMISSION_HPP
#define PHYSICS_TRANSMISSION_HPP

#include <vector>

#include "game/transmission.hpp"

namespace Physics
{

class Transmission
{
	public:
		typedef std::vector<float>::size_type GearIndex;

		float getInertia();
		float getRatio();
		float getEfficiency();

		GearIndex getLastGearIndex();
		void setCurrentGear(GearIndex gear);
		GearIndex getCurrentGear();

		Transmission(const Game::Transmission& transmission);

	private:
		GearIndex decideInitialGear();

		float efficiency;

		std::vector<float> ratios;
		std::vector<float>::size_type currentIndex;
};

};

#endif