#include "fontloader.hpp"

#include "ui.hpp"

FontLoader::FontLoader(Graphics& graphics):
	m_fontface(graphics)
{
	m_fontface.load("data/fonts/freesans.ttf",64);

	Font::setFontType("title",&m_fontface,TITLE_SIZE.getY(),Color(0,0,0));
	Font::setFontType("Label",&m_fontface,ITEM_HEIGHT,Color(0,0,0));
	Font::setFontType("Button",&m_fontface,ITEM_HEIGHT,Color(0,0,0));
	Font::setFontType("Button.active",&m_fontface,ITEM_HEIGHT,Color(0.95,0.95,0.95));
	Font::setFontType("Select",&m_fontface,ITEM_HEIGHT,Color(0,0,0));
	Font::setFontType("Select.active",&m_fontface,ITEM_HEIGHT,Color(0.95,0.95,0.95));
	Font::setFontType("Field",&m_fontface,ITEM_HEIGHT,Color(0,0,0));	
}

