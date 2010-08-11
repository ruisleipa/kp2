#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "activetextwidget.hpp"

#include "callback/callback.hpp"

class Button : public ActiveTextWidget
{
	public:
		virtual void onMouseDown(MouseEvent event);
		
		void setClickHandler(Callback0 handler);
		
		Button();
		
	private:	
		Callback0 m_click_handler;
		
};

#endif // BUTTON_HPP
