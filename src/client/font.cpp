#include "font.hpp"

#include "assert.hpp"

Font::Font(FontFace* font_face,float size,Color color)
{
	assert(font_face != 0);
	
	m_font_face=font_face;
	m_size=size;
	m_color=color;	
}

void Font::draw(std::wstring str,Vector2D pos)
{
	m_color.apply();
	m_font_face->draw(str,pos,m_size);
}

Vector2D Font::getTextSize(std::wstring str)
{
	return m_font_face->getTextSize(str,m_size);
}