#ifndef __ACTIVETEXTWIDGET_HPP
#define __ACTIVETEXTWIDGET_HPP

#include "textwidget.hpp"
#include "font.hpp"

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

		int m_mouse_over_time;
		
		static Sound m_mouse_over_sound;
		static Sound m_mouse_down_sound;
};

#endif // __ACTIVETEXTWIDGET_HPP
