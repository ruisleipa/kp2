#ifndef __EVENTLISTENER_HPP
#define __EVENTLISTENER_HPP

#include "keyevent.hpp"
#include "mouseevent.hpp"

class EventListener
{
	public:
		virtual void keyDown(KeyEvent)=0;
		virtual void keyUp(KeyEvent)=0;
		virtual void mouseDown(MouseEvent)=0;
		virtual void mouseUp(MouseEvent)=0;
		virtual void mouseMove(MouseEvent)=0;
};

#endif // __KEYEVENT_HPP
