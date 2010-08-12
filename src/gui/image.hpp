#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "widget.hpp"

#include "graphics/texture.hpp"
#include "graphics/color.hpp"

class Image : public Widget
{
	public:
		void setTexture(Texture* texture);
		Texture* getTexture();
		
		void setStretched(bool stretch);
		bool getStrecthed();
		
		void setFill(bool fill);
		bool getFill();
		
		void setColor(Color color);
		Color getColor();		
		
		virtual void onDraw(Window& window);
		
		Image();
		
	private:
		Texture* m_texture;	
		bool m_stretched;
		bool m_fill;
		Color m_color;

};

#endif // IMAGE_HPP

