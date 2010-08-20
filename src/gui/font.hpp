#ifndef FONT_HPP
#define FONT_HPP

#include "graphics/fontface.hpp"
#include "graphics/color.hpp"
#include "graphics/vector2d.hpp"
#include "graphics/window.hpp"

#include <string>
#include <map>

class Font
{
	public:
		void draw(std::wstring str,Vector2D pos);
		void draw(std::wstring str,Vector2D pos,Color color);
		void drawWrapped(std::wstring str,Vector2D pos,Vector2D size);
		void drawWrapped(std::wstring str,Vector2D pos,Vector2D size,Color color);
		Vector2D getTextSize(std::wstring str);
		Color getColor();
		
		static void setFontType(std::string name,FontFace* font_face,float size,Color color);
		
		Font(std::string type);
		Font();

	private:
		class FontType
		{
			public:
				FontFace* m_font_face;
				float m_size;
				Color m_color;
		};
		
		FontType* m_font_type;
		
		static std::map<std::string,FontType> m_font_types;
};

#endif
