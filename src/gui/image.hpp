#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "widget.hpp"

#include "graphics/texture.hpp"
#include "graphics/color.hpp"

class Image : public Widget
{
	public:
		void setTexture(const Texture& texture);
		Texture& getTexture();
		
		enum ScalingMode
		{
			NONE,
			PROPORTIONAL,
			PROPORTIONAL_FILL,
			STRETCH_FILL,
			NINE_SLICE
		};
		
		void setScalingMode(ScalingMode mode);
		
		void setNineSliceCorners(Vector2D topLeft, Vector2D bottomRight);
		
		void setColor(Color color);
		Color getColor();
		
		virtual void handleEvent(Event* event);
		
		Image();
		
	private:
		void handleDrawEvent(DrawEvent* event);
	
		Texture texture;
		ScalingMode scalingMode;
		Vector2D nineSliceTopLeft;
		Vector2D nineSliceBottomRight;
		Color color;

};

#endif // IMAGE_HPP

