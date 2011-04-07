#ifndef PHYSICS_TRANSMISSION_HPP
#define PHYSICS_TRANSMISSION_HPP

#include <vector>

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
		
		Transmission(std::vector<float> ratios, size_t neutralIndex,
			float efficiency, float differentialRatio, float driveshaftInertia);

	private:
		float differentialRatio;
		float efficiency;
		float driveshaftInertia;
		
		std::vector<float> ratios;
		size_t neutralIndex;
		
		size_t currentIndex;
};

#endif
