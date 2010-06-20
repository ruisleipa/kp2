#ifndef __FONTLOADER_HPP
#define __FONTLOADER_HPP

#include "fontface.hpp"

class FontLoader
{
	public:
		FontLoader(Graphics& graphics);

	private:
		FontFace m_fontface;		
};

#endif // __FONTLOADER_HPP
