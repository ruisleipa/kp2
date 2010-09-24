#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "widget.hpp"

#include "graphics/texture.hpp"
#include "graphics/color.hpp"

class Image : public Widget
{
	public:
		void setTexture(Texture& texture);
		Texture& getTexture();
		
		void setStretched(bool stretch);
		bool getStrecthed();
		
		void setFill(bool fill);
		bool getFill();
		
		void setColor(Color color);
		Color getColor();		
		
		virtual void onDraw(DrawEvent event);
		
		Image();
		
	private:
		Texture texture;	
		bool stretched;
		bool fill;
		Color color;

};

#endif // IMAGE_HPP

