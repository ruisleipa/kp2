#ifndef GAME_CYLINDERBLOCK_HPP
#define GAME_CYLINDERBLOCK_HPP

#include "part.hpp"
#include "cylinderhead.hpp"
#include "crankshaft.hpp"

#include <string>

namespace Game
{

class CylinderBlock : public Part
{
	public:
		int getCylinderCount() const;
		double getBore() const;
		double getHeight() const;

		void applyPropertiesOf(const CylinderBlock& cylinderBlock);

		CylinderBlock(int cylinderCount, double bore, double height);
		CylinderBlock(const Json::Value& value);
		virtual void save(Json::Value& value) const;

	private:
		TypedSlot<CylinderHead> cylinderHead;
		TypedSlot<Crankshaft> crankshaft;

		int cylinderCount;
		double bore;
		double height;
};

};

#endif
