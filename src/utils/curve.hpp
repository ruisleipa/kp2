#ifndef UTILS_CURVE_HPP
#define UTILS_CURVE_HPP

#include <map>

class Packet;

class Curve
{
	public:
		void addPoint(int position, float value);
		float getValue(float position) const;
		float getMax() const;

	private:
		std::map<int, float> points;
		
		friend Packet& operator<<(Packet& packet,const Curve& curve);
		friend Packet& operator>>(Packet& packet,Curve& curve);
	
};


#endif
