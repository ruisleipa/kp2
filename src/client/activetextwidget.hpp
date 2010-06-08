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
		
		virtual void mouseOn();
		virtual void mouseOut();		
		virtual void mouseDown(MouseEvent);
		
		virtual void draw(Graphics& graphics);
		
		ActiveTextWidget();
	
	protected:
	
		bool isMouseOver();
	
	private:	
		Font m_active_font;
		
		bool m_mouse_over;	
		bool m_animate;

		int m_mouse_over_time;
		
		static Sound m_mouse_over_sound;
		static Sound m_mouse_down_sound;
};

#endif // __ACTIVETEXTWIDGET_HPP
