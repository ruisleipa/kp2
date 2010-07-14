#ifndef FONTLOADER_HPP
#define FONTLOADER_HPP

#include "fontface.hpp"

class FontLoader
{
	public:
		FontLoader(Graphics& graphics);

	private:
		FontFace m_fontface;		
};

#endif // FONTLOADER_HPP
