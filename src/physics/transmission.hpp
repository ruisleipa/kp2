#ifndef PHYSICS_TRANSMISSION_HPP
#define PHYSICS_TRANSMISSION_HPP

#include <vector>

namespace Physics
{

class Transmission
{
	public:	
		float getRatio();
		bool isOnNeutral();
		
		void lowerGear();
		void upperGear();
		
		float getEfficiency();
		
		float getDifferentialRatio();
		float getDriveshaftInertia();
		
		Transmission(std::vector<float> ratios, std::vector<float>::size_type neutralIndex,
			float efficiency, float differentialRatio, float driveshaftInertia);

	private:
		float differentialRatio;
		float efficiency;
		float driveshaftInertia;
		
		std::vector<float> ratios;
		std::vector<float>::size_type neutralIndex;
		
		std::vector<float>::size_type currentIndex;
};

};

#endif
