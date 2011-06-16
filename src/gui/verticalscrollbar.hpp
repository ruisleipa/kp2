#ifndef GUI_VERTICALSCROLLBAR_HPP
#define GUI_VERTICALSCROLLBAR_HPP

#include "scrollbar.hpp"

class VerticalScrollBar : public ScrollBar
{
	protected:
		virtual int getShortAxis(Vector2D value);
		virtual int getLongAxis(Vector2D value);
		
		virtual Vector2D convertToReal(int shortAxis, int longAxis);
		
};

#endif
