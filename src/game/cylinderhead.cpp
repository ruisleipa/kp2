#include "cylinderhead.hpp"

namespace Game
{

int CylinderHead::getCylinderCount() const
{
	return cylinderCount;
}

double CylinderHead::getBore() const
{
	return bore;
}

double CylinderHead::getChamberHeight() const
{
	return chamberHeight;
}

void CylinderHead::applyPropertiesOf(const CylinderHead& cylinderHead)
{
	cylinderCount = cylinderHead.getCylinderCount();
	bore = cylinderHead.getBore();
	chamberHeight = cylinderHead.getChamberHeight();
}

CylinderHead::CylinderHead(int cylinderCount, double bore, double chamberHeight):
	cylinderCount(cylinderCount),
	bore(bore),
	chamberHeight(chamberHeight)
{

}

CylinderHead::CylinderHead(const Json::Value& value):
	Part(value)
{
	cylinderCount = value["cylinderCount"].asUInt();
	bore = value["bore"].asDouble();
	chamberHeight = value["chamberHeight"].asDouble();
}

void CylinderHead::save(Json::Value& value) const
{
	Part::save(value);

	value["type"] = "CylinderHead";
	value["cylinderCount"] = cylinderCount;
	value["bore"] = bore;
	value["chamberHeight"] = chamberHeight;
}

}
