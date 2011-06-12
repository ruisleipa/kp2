#include "gauge.hpp"

void Gauge::handleEvent(Event* event)
{
	if(dynamic_cast<DrawEvent*>(event))
		handleDrawEvent(dynamic_cast<DrawEvent*>(event));
}

void Gauge::setValueRange(float min, float max)
{
	minValue = min;
	maxValue = max;
}

void Gauge::setAngleRange(float min, float max)
{
	minAngle = min;
	maxAngle = max;
}

void Gauge::setGaugeTexture(Texture gauge)
{
	this->gauge = gauge;
}

void Gauge::setNeedleTexture(Texture needle)
{
	this->needle = needle;
}

void Gauge::setValue(float value)
{
	this->value = value;
}

Gauge::Gauge():
	minValue(0),
	maxValue(100),
	minAngle(0),
	maxAngle(0)
{

}

void Gauge::handleDrawEvent(DrawEvent* event)
{
	Color(1, 1, 1, 1).apply();

	gauge.draw(event->getAreaPosition(), event->getAreaSize());
	
	float valueRange = maxValue - minValue;
	
	float valueRatio = (value - minValue) / valueRange;
	
	float angleRange = maxAngle - minAngle;
	
	float needleAngle = minAngle + angleRange * valueRatio;
	
	float needleAspectRatio = needle.getSize().getX() / needle.getSize().getY();
	
	Vector2D needleSize(event->getAreaSize().getY() * needleAspectRatio, event->getAreaSize().getY());
	Vector2D needleAxlePosition = event->getAreaPosition() + (event->getAreaSize() / 2.0);
	
	glPushMatrix();
	
	glTranslatef(needleAxlePosition.getX(), needleAxlePosition.getY(), 0);
	glRotatef(needleAngle, 0, 0, 1);
	glTranslatef(-(needleSize.getX()/2.0), -(needleSize.getY()/2.0), 0);
	
	needle.draw(Vector2D(0, 0), needleSize);
	
	glPopMatrix();
}
