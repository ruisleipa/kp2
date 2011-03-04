#ifndef FONTLOADER_HPP
#define FONTLOADER_HPP

#include "graphics/fontface.hpp"

class FontLoader
{
	public:
		FontLoader(Window& window);
		
		void freeTextures();
		void uploadTextures();
		void reload();

	private:
		Window& window;
	
		FontFace font;		
		FontFace smallFont;		
};

#endif // FONTLOADER_HPP
