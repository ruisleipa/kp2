#ifndef FONTFACE_HPP
#define FONTFACE_HPP

#include "texture.hpp"
#include "vector2d.hpp"
#include "window.hpp"
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
		void draw(Window& window,std::wstring str,Vector2D pos,float char_height);
		void drawWrapped(Window& window,std::wstring str,Vector2D pos,Vector2D size,float char_height);
		Vector2D getTextSize(Window& window,std::wstring str,float char_height);

		FontFace();
		FontFace(std::string fontfile,int fontsize);
		~FontFace();

	private:
		FontFace(const FontFace&);
		FontFace& operator=(const FontFace&);

		void unload();

		int loadPage(unsigned int pagenum);

		std::string m_name;
		TTF_Font* m_font;
		int m_height;
		std::map<unsigned long,FontPage> m_font_pages;
};

#endif
