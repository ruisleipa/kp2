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
		
		virtual void onDraw(DrawEvent event);
		
		virtual void autoSize();
		
		ActiveTextWidget();
	
	protected:
	
		bool isMouseOver();
	
	private:	
		Font activeFont;
		Font borderFont;
		
		bool mouseOverFlag;	
		bool doAnimate;

		Timer mouseOverTimer;
		
		static Sound mouseOverSound;
		static Sound mouseDownSound;
};

#endif // ACTIVETEXTWIDGET_HPP
