#include "cylinderblock.hpp"

namespace Game
{

int CylinderBlock::getCylinderCount() const
{
	return cylinderCount;
}

double CylinderBlock::getBore() const
{
	return bore;
}

double CylinderBlock::getHeight() const
{
	return height;
}

void CylinderBlock::applyPropertiesOf(const CylinderBlock& cylinderBlock)
{
	cylinderCount = cylinderBlock.getCylinderCount();
	bore = cylinderBlock.getBore();
	height = cylinderBlock.getHeight();
}

CylinderBlock::CylinderBlock(int cylinderCount, double bore, double height):
	cylinderCount(cylinderCount),
	bore(bore),
	height(height)
{
	registerSlot("cylinderHead", &cylinderHead);
	registerSlot("crankshaft", &crankshaft);
}

CylinderBlock::CylinderBlock(const Json::Value& value):
	Part(value),
	cylinderHead(value["cylinderHead"]),
	crankshaft(value["crankshaft"]),
	cylinderCount(value["cylinderCount"].asUInt()),
	bore(value["bore"].asDouble()),
	height(value["height"].asDouble())
{
	registerSlot("cylinderHead", &cylinderHead);
	registerSlot("crankshaft", &crankshaft);
}

void CylinderBlock::save(Json::Value& value) const
{
	Part::save(value);

	value["type"] = "CylinderBlock";
	value["cylinderCount"] = cylinderCount;
	value["bore"] = bore;
	value["height"] = height;
	cylinderHead.save(value["cylinderHead"]);
	crankshaft.save(value["crankshaft"]);
}

}
