#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "activetextwidget.hpp"

#include <tr1/functional>

class Button : public ActiveTextWidget
{
	public:
		virtual void onMouseDown(MouseEvent event);
		
		void setClickHandler(std::tr1::function<void()> handler);
		
		Button();
		
	private:	
		std::tr1::function<void()> clickHandler;
		
};

#endif // BUTTON_HPP

