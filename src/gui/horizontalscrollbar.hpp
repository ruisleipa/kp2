#ifndef GUI_HORIZONTALSCROLLBAR_HPP
#define GUI_HORIZONTALSCROLLBAR_HPP

#include "scrollbar.hpp"

class HorizontalScrollBar : public ScrollBar
{
	protected:
		virtual int getShortAxis(Vector2D value);
		virtual int getLongAxis(Vector2D value);
		
		virtual Vector2D convertToReal(int shortAxis, int longAxis);
		
};

#endif
