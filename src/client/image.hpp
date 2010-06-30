#ifndef __IMAGE_HPP
#define __IMAGE_HPP

#include "widget.hpp"

#include "texture.hpp"

class Image : public Widget
{
	public:
		void setTexture(Texture* texture);
		Texture* getTexture();
		
		void setStretched(bool stretch);
		bool getStrecthed();
		
		virtual void onDraw(Graphics& graphics);
		
		Image();
		
	private:
		Texture* m_texture;	
		bool m_stretched;

};

#endif // __IMAGE_HPP

