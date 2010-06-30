#ifndef __BUTTON_HPP
#define __BUTTON_HPP

#include "activetextwidget.hpp"

class Button : public ActiveTextWidget
{
	public:
		virtual void onClick();
	
		virtual void onMouseDown(MouseEvent event);
		
		Button();
		
	private:
		
};

#endif // __BUTTON_HPP

