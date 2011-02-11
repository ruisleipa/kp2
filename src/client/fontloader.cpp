#include "fontloader.hpp"

#include "ui.hpp"

#include "graphics/color.hpp"
#include "gui/font.hpp"

const Color BORDER(0, 0, 0);
const Color NORMAL(0, 0, 0);
const Color PASSIVE(0.5, 0.5, 0.5);
const Color ACTIVE(1, 1, 1);

FontLoader::FontLoader(Window& window):
	font(window, "data/fonts/dejavusansbold.ttf", window.getSize().getY()*(12.0/480.0)),
	smallFont(window, "data/fonts/dejavusansbold.ttf", window.getSize().getY()*(8.0/480.0))
{
	Font::setFontType("title", font, NORMAL);
	Font::setFontType("small", smallFont, NORMAL);
	Font::setFontType("Label", font, NORMAL);
	Font::setFontType("Textborder", font, BORDER);
	Font::setFontType("Button", font, PASSIVE);
	Font::setFontType("Button.active", font, ACTIVE);
	Font::setFontType("Select", font, PASSIVE);
	Font::setFontType("Select.active", font, ACTIVE);
	Font::setFontType("Field", font, NORMAL);
	Font::setFontType("Listbox", smallFont, NORMAL);	
}

