#ifndef __FONT_HPP
#define __FONT_HPP

#include "fontface.hpp"
#include "color.hpp"
#include "vector2d.hpp"

#include <string>

class Font
{
	public:
		Font(FontFace* font_face,float size,Color color);

		void draw(std::wstring str,Vector2D pos);
		Vector2D getTextSize(std::wstring str);
		
	private:
		FontFace* m_font_face;
		float m_size;
		Color m_color;
};

#endif
