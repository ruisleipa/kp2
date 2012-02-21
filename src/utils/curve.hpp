#ifndef UTILS_CURVE_HPP
#define UTILS_CURVE_HPP

#include <map>

#include "net/packet.hpp"

class Curve
{
	public:
		void addPoint(int position, float value);
		float getValue(float position) const;
		float getMax() const;

	private:
		std::map<int, float> points;
		
		friend Net::Packet& operator<<(Net::Packet& packet,const Curve& curve);
		friend Net::Packet& operator>>(Net::Packet& packet,Curve& curve);
	
};


#endif
