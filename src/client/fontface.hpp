#ifndef __FONTFACE_HPP
#define __FONTFACE_HPP

#include "texture.hpp"
#include "vector2d.hpp"
#include "color.hpp"
#include <SDL/SDL_ttf.h>
#include <map>

#define FONT_PAGE_SIZE 256

class LetterRectangle
{
	public:
		Vector2D position;
		Vector2D size;
};

class FontPage
{
	public:
		Texture letters;
		LetterRectangle letter_rectangles[FONT_PAGE_SIZE];
};

class FontFace
{
	public:
		int load(std::string fontfile,int fontsize);
		void draw(std::wstring str,Vector2D pos,float char_height);
		void drawWrapped(std::wstring str,Vector2D pos,Vector2D size);
		Vector2D getTextSize(std::wstring str,float char_height);
		FontFace();
		FontFace(std::string fontfile,int fontsize);
		~FontFace();

	private:
		FontFace(const FontFace&);
		FontFace& operator=(const FontFace&);

		void unload();

		int loadPage(unsigned int pagenum);

		TTF_Font* m_font;
		int m_height;
		std::map<unsigned long,FontPage> m_font_pages;
};

#endif
