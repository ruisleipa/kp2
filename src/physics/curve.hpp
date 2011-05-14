#ifndef PHYSICS_CURVE_HPP
#define PHYSICS_CURVE_HPP

#include <map>

class Curve
{
	public:
		void addPoint(int position, float value);
		float getValue(float position) const;
		float getMax() const;

	private:
		std::map<int, float> curve;
	
};


#endif
