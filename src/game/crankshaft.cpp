#include "crankshaft.hpp"

namespace Game
{

double Crankshaft::getStroke() const
{
	return stroke;
}

void Crankshaft::applyPropertiesOf(const Crankshaft& crankshaft)
{
	stroke = crankshaft.getStroke();
}

Crankshaft::Crankshaft(double stroke):
	stroke(stroke)
{

}

Crankshaft::Crankshaft(const Json::Value& value):
	Part(value)
{
	stroke = value["stroke"].asDouble();
}

void Crankshaft::save(Json::Value& value) const
{
	Part::save(value);

	value["type"] = "Crankshaft";
	value["stroke"] = stroke;
}

}
