#ifndef FONTFACE_HPP
#define FONTFACE_HPP

#include "texture.hpp"
#include "vector2d.hpp"
#include "window.hpp"
#include "utils/noncopyable.hpp"
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

class FontFace: public NonCopyable
{
	public:
		void draw(std::wstring str,Vector2D pos,float char_height);
		void drawWrapped(std::wstring str,Vector2D pos,Vector2D size,float char_height);
		Vector2D getTextSize(std::wstring str,float char_height);

		FontFace(Window& window,std::string fontfile,int fontsize);
		~FontFace();

	private:
		int load(std::string fontfile,int fontsize);
				
		void unload();

		int loadPage(unsigned int pagenum);

		Window& window;
		int height;
		TTF_Font* font;
		std::map<unsigned long,FontPage> fontPages;
};

#endif
