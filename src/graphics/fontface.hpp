#ifndef FONTFACE_HPP
#define FONTFACE_HPP

#include "texture.hpp"
#include "vector2d.hpp"
#include "window.hpp"
#include "utils/noncopyable.hpp"
#include <SDL/SDL_ttf.h>
#include <map>
#include <stdexcept>
#include <tr1/memory>

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

class FontFile
{
	public:
		TTF_Font* font;
		
		FontFile(const std::string& filename, int fontsize)
		{
			if(!TTF_WasInit())
				TTF_Init();

			font = TTF_OpenFont(filename.c_str(), fontsize);

			if(!font)
			{
				std::string error;
		
				error += "Unable to load image: '";
				error += filename;
				error += "'";
				
				throw std::runtime_error(error);
			}
		}
		
		~FontFile()
		{
			if(font)
				TTF_CloseFont(font);
		}
};

class FontFace
{
	public:
		void draw(std::wstring str,Vector2D pos);
		void drawWrapped(std::wstring str,Vector2D pos,Vector2D size);
		Vector2D getTextSize(std::wstring str);

		void freeTextures();
		void uploadTextures();
		
		FontFace(Window& window,std::string fontfile,int fontsize);
		~FontFace();

	private:
		int load(std::string fontfile,int fontsize);
				
		void unload();

		int loadPage(unsigned int pagenum);

		Window* window;
		int height;
		std::tr1::shared_ptr<FontFile> font;
		std::map<unsigned long,FontPage> fontPages;
};

#endif
