#ifndef PHYSICS_AIR_HPP
#define PHYSICS_AIR_HPP

namespace Physics
{

class Air
{
	public:
		float getMass();
		float getVolume();
		float getTemperature();
		float getPressure();
		
		void compress(float newVolume);
		void restrict(float newVolume);
		
		Air(float mass, float volume, float temperatureInKelvin);

	private:
		float mass;		
		float volume;
		float temperatureInKelvin;
};

};

#endif
