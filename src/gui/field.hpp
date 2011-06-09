#ifndef FIELD_HPP
#define FIELD_HPP

#include "textwidget.hpp"

#include "utils/timer.hpp"

class Field : public TextWidget
{
	public:
		virtual void handleEvent(Event* event);
		
		Field();
		
		virtual Vector2D getAutoSize();
		
	private:
		void handleDrawEvent(DrawEvent* event);
		void handleKeyDownEvent(KeyDownEvent* event);
		
		void handleFocusEvent();
		void handleBlurEvent();
	
		size_t cursorPosition;
		
		Timer blinkTimer;
		bool isFocused;
};

#endif // FIELD_HPP
