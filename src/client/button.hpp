#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "activetextwidget.hpp"

class Button : public ActiveTextWidget
{
	public:
		virtual void onClick();
	
		virtual void onMouseDown(MouseEvent event);
		
		Button();
		
	private:
		
};

#endif // BUTTON_HPP

