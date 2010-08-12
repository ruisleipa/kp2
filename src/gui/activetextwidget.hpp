#ifndef ACTIVETEXTWIDGET_HPP
#define ACTIVETEXTWIDGET_HPP

#include "utils/timer.hpp"

#include "sounds/sound.hpp"

#include "textwidget.hpp"
#include "font.hpp"

class ActiveTextWidget : public TextWidget
{
	public:
		void setActiveFont(Font font);
		Font& getActiveFont();
		
		virtual void onMouseOn();
		virtual void onMouseOut();		
		virtual void onMouseDown(MouseEvent);
		
		virtual void onDraw(Window& window);
		
		virtual void autoSize();
		
		ActiveTextWidget();
	
	protected:
	
		bool isMouseOver();
	
	private:	
		Font m_active_font;
		Font m_border_font;
		
		bool m_mouse_over;	
		bool m_animate;

		Timer m_mouse_over_timer;
		
		static Sound m_mouse_over_sound;
		static Sound m_mouse_down_sound;
};

#endif // ACTIVETEXTWIDGET_HPP
