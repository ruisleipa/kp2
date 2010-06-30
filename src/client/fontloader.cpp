#include "fontloader.hpp"

#include "ui.hpp"

const Color NORMAL(0,0,0);
const Color PASSIVE(0.7,0.7,0.7);
const Color ACTIVE(1,1,1);

FontLoader::FontLoader(Graphics& graphics):
	m_fontface(graphics)
{
	m_fontface.load("data/fonts/freesans.ttf",64);

	Font::setFontType("title",&m_fontface,TITLE_SIZE.getY(),NORMAL);
	Font::setFontType("small",&m_fontface,ITEM_HEIGHT*0.75,NORMAL);
	Font::setFontType("Label",&m_fontface,ITEM_HEIGHT,NORMAL);
	Font::setFontType("Button",&m_fontface,ITEM_HEIGHT,PASSIVE);
	Font::setFontType("Button.active",&m_fontface,ITEM_HEIGHT,ACTIVE);
	Font::setFontType("Select",&m_fontface,ITEM_HEIGHT,PASSIVE);
	Font::setFontType("Select.active",&m_fontface,ITEM_HEIGHT,ACTIVE);
	Font::setFontType("Field",&m_fontface,ITEM_HEIGHT,NORMAL);	
}

