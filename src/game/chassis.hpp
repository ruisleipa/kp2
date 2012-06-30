#ifndef GAME_CHASSIS_HPP
#define GAME_CHASSIS_HPP

#include "part.hpp"
#include "cylinderblock.hpp"

namespace Game
{

class Chassis : public Part
{
	public:
		class Dimensions
		{
			public:
				float length;
				float width;
				float height;
				float wheelbase;
				float axleTrack;
		};

		class EngineConstraints
		{
			public:
				int maxVolume;
				int maxCylinderCount;
		};

		float getDragCoefficient() const;
		const Dimensions& getDimensions() const;
		const EngineConstraints& getEngineConstraints() const;

		void applyPropertiesOf(const Chassis& chassis);

		Chassis(float mass, float dragCoefficient, const Dimensions&, const EngineConstraints&);
		Chassis(const Json::Value&);
		virtual void save(Json::Value& value) const;

	private:
		TypedSlot<CylinderBlock> cylinderBlock;

		float dragCoefficient;
		Dimensions dimensions;
		EngineConstraints engineConstraints;
};

};

#endif

