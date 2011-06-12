#ifndef CLIENT_GAUGE_HPP
#define CLIENT_GAUGE_HPP

#include "graphics/texture.hpp"
#include "gui/widget.hpp"

class Gauge : public Widget
{
	public:
		virtual void handleEvent(Event* event);
		
		void setValueRange(float min, float max);
		void setAngleRange(float min, float max);
		void setGaugeTexture(Texture gauge);
		void setNeedleTexture(Texture needle);
		
		void setValue(float value);
		
		Gauge();
		
	private:
		void handleDrawEvent(DrawEvent* event);
		
		Texture gauge;
		Texture needle;
		
		float minValue;
		float maxValue;
		float minAngle;
		float maxAngle;
		
		float value;
};

#endif
