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
		
		virtual void handleEvent(Event* event);
		
		virtual Vector2D getAutoSize();
		
		ActiveTextWidget();
	
	protected:	
		bool isMouseOver();
	
	private:
		void handleMouseOverEvent(MouseOverEvent* event);
		void handleMouseOutEvent(MouseOutEvent* event);
		void handleMouseDownEvent(MouseDownEvent* event);
		void handleDrawEvent(DrawEvent* event);
	
		Font activeFont;
		Font borderFont;
		
		bool mouseOverFlag;	
		bool doAnimate;

		Timer mouseOverTimer;
		
		static bool soundsLoaded;
		static Sound mouseOverSound;
		static Sound mouseDownSound;
};

#endif // ACTIVETEXTWIDGET_HPP
