#include "curve.hpp"

#include <algorithm>
#include <stdint.h>
#include <iostream>

#include "net/packet.hpp"

void Curve::addPoint(int position, float value)
{
	points[position] = value;
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

Curve::Curve(const Json::Value& value)
{
	for(auto point : value)
	{
		int position = point["position"].asInt();
		float value = point["value"].asDouble();

		addPoint(position, value);
	}
}

void Curve::save(Json::Value& value) const
{
	value.resize(0);

	for(std::pair<int, float> point : points)
	{
		Json::Value saved;

		saved["position"] = point.first;
		saved["value"] = point.second;

		value.append(saved);
	}
}
