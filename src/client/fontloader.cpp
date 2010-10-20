#include "fontloader.hpp"

#include "ui.hpp"

#include "graphics/color.hpp"
#include "gui/font.hpp"

const Color BORDER(0,0,0);
const Color NORMAL(0,0,0);
const Color PASSIVE(0.7,0.7,0.7);
const Color ACTIVE(1,1,1);

FontLoader::FontLoader(Window& window):
	font(window,"data/fonts/freesans.ttf",18)
{
	Font::setFontType("title",&font,TITLE_SIZE.getY(),NORMAL);
	Font::setFontType("small",&font,0.03,NORMAL);
	Font::setFontType("Label",&font,ITEM_HEIGHT,NORMAL);
	Font::setFontType("Textborder",&font,ITEM_HEIGHT,BORDER);
	Font::setFontType("Button",&font,ITEM_HEIGHT,PASSIVE);
	Font::setFontType("Button.active",&font,ITEM_HEIGHT,ACTIVE);
	Font::setFontType("Select",&font,ITEM_HEIGHT,PASSIVE);
	Font::setFontType("Select.active",&font,ITEM_HEIGHT,ACTIVE);
	Font::setFontType("Field",&font,ITEM_HEIGHT,NORMAL);	
	Font::setFontType("Listbox",&font,0.03,NORMAL);	
}

