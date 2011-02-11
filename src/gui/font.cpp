#include "font.hpp"

#include "debug/assert.hpp"

std::map<std::string, Font::FontType> Font::fontTypes;

void Font::draw(std::wstring str, Vector2D pos)
{
	if(!fontType)
		return;
		
	fontType->color.apply();
	fontType->fontFace->draw(str, pos);
}

void Font::draw(std::wstring str, Vector2D pos, Color color)
{
	if(!fontType)
		return;
		
	color.apply();
	fontType->fontFace->draw(str, pos);
}

void Font::drawWrapped(std::wstring str, Vector2D pos, Vector2D size)
{
	if(!fontType)
		return;
		
	fontType->color.apply();
	fontType->fontFace->drawWrapped(str, pos, size);
}

void Font::drawWrapped(std::wstring str, Vector2D pos, Vector2D size, Color color)
{
	if(!fontType)
		return;
		
	color.apply();
	fontType->fontFace->drawWrapped(str, pos, size);
}

Vector2D Font::getTextSize(std::wstring str)
{
	if(!fontType)
		return Vector2D(0, 0);
	
	return fontType->fontFace->getTextSize(str);
}

Color Font::getColor()
{
	if(!fontType)
		return Color();
		
	return fontType->color;
}

Font::Font(std::string type):
	fontType(0)
{
	std::map<std::string, FontType>::iterator i;
	
	i = fontTypes.find(type);
	
	if(i != fontTypes.end())
		fontType=&((*i).second);		
}

Font::Font():
	fontType(0)
{
	
}

void Font::setFontType(std::string name, FontFace& fontFace, Color color)
{
	FontType newFontType;
	
	newFontType.fontFace = &fontFace;
	newFontType.color = color;

	fontTypes[name] = newFontType;
}

