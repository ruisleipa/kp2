#include "font.hpp"

#include "debug/assert.hpp"

std::map<std::string,Font::FontType> Font::m_font_types;

void Font::draw(std::wstring str,Vector2D pos)
{
	if(!m_font_type)
		return;
		
	m_font_type->m_color.apply();
	m_font_type->m_font_face->draw(str,pos);
}

void Font::draw(std::wstring str,Vector2D pos,Color color)
{
	if(!m_font_type)
		return;
		
	color.apply();
	m_font_type->m_font_face->draw(str,pos);
}

void Font::drawWrapped(std::wstring str,Vector2D pos,Vector2D size)
{
	if(!m_font_type)
		return;
		
	m_font_type->m_color.apply();
	//m_font_type->m_font_face->draw(str,pos);
	m_font_type->m_font_face->drawWrapped(str,pos,size);
}

void Font::drawWrapped(std::wstring str,Vector2D pos,Vector2D size,Color color)
{
	if(!m_font_type)
		return;
		
	color.apply();
	m_font_type->m_font_face->drawWrapped(str,pos,size);
}

Vector2D Font::getTextSize(std::wstring str)
{
	if(!m_font_type)
		return Vector2D(0,0);
	
	return m_font_type->m_font_face->getTextSize(str);
}

Color Font::getColor()
{
	if(!m_font_type)
		return Color();
		
	return m_font_type->m_color;
}

Font::Font(std::string type):
	m_font_type(0)
{
	std::map<std::string,FontType>::iterator i;
	
	i=m_font_types.find(type);
	
	if(i==m_font_types.end())
		return;
	
	m_font_type=&((*i).second);		
}

Font::Font():
	m_font_type(0)
{
	
}

void Font::setFontType(std::string name,FontFace* font_face,float size,Color color)
{
	assert(font_face != 0);
	
	if(font_face == 0)
		return;

	FontType font_info;
	
	font_info.m_font_face=font_face;
	font_info.m_size=size;
	font_info.m_color=color;

	m_font_types[name]=font_info;
}

