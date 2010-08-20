#ifndef FONTLOADER_HPP
#define FONTLOADER_HPP

#include "graphics/fontface.hpp"

class FontLoader
{
	public:
		FontLoader(Window& window);

	private:
		FontFace font;		
};

#endif // FONTLOADER_HPP
