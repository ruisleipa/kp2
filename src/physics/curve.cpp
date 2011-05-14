#include "curve.hpp"

#include <algorithm>

void Curve::addPoint(int position, float value)
{
	curve[position] = value;
}

float Curve::getValue(float position) const
{
	//TODO: fix output for out of range position

	std::map<int, float>::const_iterator previous = curve.begin();
	std::map<int, float>::const_iterator current = curve.begin();
	
	while(current != curve.end() && current->first <= position)
	{
		previous = current;
		
		++current;
	}
	
	if(current == curve.end())
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

	for(std::map<int, float>::const_iterator i = curve.begin(); i != curve.end(); ++i)
	{		
		if(i == curve.begin())
			value = i->second;
		else
			value = std::max(value, i->second);	
	}
	
	return value;
}
