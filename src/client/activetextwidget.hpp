#ifndef ACTIVETEXTWIDGET_HPP
#define ACTIVETEXTWIDGET_HPP

#include "textwidget.hpp"
#include "font.hpp"
#include "timer.hpp"

#include "sound.hpp"

class ActiveTextWidget : public TextWidget
{
	public:
		void setActiveFont(Font font);
		Font& getActiveFont();
		
		virtual void onMouseOn();
		virtual void onMouseOut();		
		virtual void onMouseDown(MouseEvent);
		
		virtual void onDraw(Graphics& graphics);
		
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
