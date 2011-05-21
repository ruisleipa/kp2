#include "curve.hpp"

#include <algorithm>
#include <stdint.h>
#include <iostream>

#include "net/packet.hpp"

void Curve::addPoint(int position, float value)
{
	points[position] = value;
	
	std::cout << position << "->" << value << std::endl;
}

float Curve::getValue(float position) const
{
	//TODO: fix output for out of range position

	std::map<int, float>::const_iterator previous = points.begin();
	std::map<int, float>::const_iterator current = points.begin();
	
	while(current != points.end() && current->first <= position)
	{
		previous = current;
		
		++current;
	}
	
	if(current == points.end())
	{
		current = previous;
	}
	
	int lowPosition = previous->first;
	int highPosition = current->first;
	float lowValue = previous->second;
	float highValue = current->second;
	
	float amount;
	
	if(lowPosition != position)
		amount = float(position - lowPosition) / float(highPosition - lowPosition);
	else
		amount = 0.0;
	
	float value = lowValue + ((highValue - lowValue) * amount);

	return value;
}

float Curve::getMax() const
{
	float value = 0.0;

	for(std::map<int, float>::const_iterator i = points.begin(); i != points.end(); ++i)
	{		
		if(i == points.begin())
			value = i->second;
		else
			value = std::max(value, i->second);	
	}
	
	return value;
}

Packet& operator<<(Packet& packet, const Curve& curve)
{
	packet << uint32_t(curve.points.size());
	
	for(std::map<int, float>::const_iterator i = curve.points.begin(); i != curve.points.end(); ++i)
	{		
		packet << int32_t(i->first);
		packet << float(i->second);
	}
	
	return packet;
}

Packet& operator>>(Packet& packet, Curve& curve)
{
	curve.points.clear();
	
	uint32_t count;
	
	packet >> count;
	
	for(int i = 0; i < count; i++)
	{		
		int32_t position;
		float value;
		
		packet >> position;
		packet >> value;
		
		curve.addPoint(position, value);
	}
	
	return packet;
}
