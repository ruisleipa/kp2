#include "fontloader.hpp"

#include "ui.hpp"

#include "graphics/color.hpp"
#include "gui/font.hpp"

const Color BORDER(0, 0, 0);
const Color NORMAL(0, 0, 0);
const Color PASSIVE(0.5, 0.5, 0.5);
const Color ACTIVE(1, 1, 1);

FontLoader::FontLoader(Window& window):
	window(window),
	font(window, "data/fonts/dejavusans.ttf", window.getSize().getY()*(12.0/480.0)),
	smallFont(window, "data/fonts/dejavusans.ttf", window.getSize().getY()*(11.0/480.0)),
	titleFont(window, "data/fonts/dejavusansboldoblique.ttf", window.getSize().getY()*(32.0/480.0))
{
	Font::setFontType("title", titleFont, NORMAL);
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

void FontLoader::freeTextures()
{
	font.freeTextures();
	smallFont.freeTextures();
	titleFont.freeTextures();
}

void FontLoader::uploadTextures()
{
	font.uploadTextures();
	smallFont.uploadTextures();
	titleFont.uploadTextures();
}

void FontLoader::reload()
{	
	font = FontFace(window, "data/fonts/dejavusans.ttf", window.getSize().getY()*(12.0/480.0));
	smallFont = FontFace(window, "data/fonts/dejavusans.ttf", window.getSize().getY()*(11.0/480.0));
	titleFont = FontFace(window, "data/fonts/dejavusansboldoblique.ttf", window.getSize().getY()*(32.0/480.0));
}

