#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "activetextwidget.hpp"

#include <tr1/functional>

class Button : public ActiveTextWidget
{
	public:
		virtual void handleEvent(Event* event);
		
		void setClickHandler(std::tr1::function<void()> handler);
		
		Button();
		
	private:	
		void handleMouseDownEvent(MouseDownEvent* event);
	
		std::tr1::function<void()> clickHandler;
		
};

#endif // BUTTON_HPP

