#ifndef GUI_SCROLLBAR_HPP
#define GUI_SCROLLBAR_HPP

#include "widget.hpp"
#include "graphics/texture.hpp"

#include <tr1/functional>

class ScrollBar : public Widget
{
	public:
		void setChangeHandler(std::tr1::function<void(int)> handler);
		
		void setRange(int min, int max);
		void setThumbSize(int size);
		
		int getValue();
		
		ScrollBar();
		
		virtual void handleEvent(Event* event);
		
	protected:
		virtual int getShortAxis(Vector2D value) = 0;
		virtual int getLongAxis(Vector2D value) = 0;
		
		virtual Vector2D convertToReal(int shortAxis, int longAxis) = 0;
		
	private:
		void handleDrawEvent(DrawEvent* event);
		void handleMouseDownEvent(MouseDownEvent* event);
		
		void tickDown();
		void tickUp();
		
		int min;
		int max;
		int value;
		int thumbSize;
		
		std::tr1::function<void(int)> changeHandler;
		
		static Texture arrowUp;
		static Texture arrowDown;
		static bool haveTexturesBeenLoaded;
};

#endif
