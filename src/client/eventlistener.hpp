#ifndef __EVENTLISTENER_HPP
#define __EVENTLISTENER_HPP

class KeyEvent;
class MouseEvent;
class Graphics;

class EventListener
{
	public:
		virtual void doKeyDown(KeyEvent event);
		virtual void doKeyUp(KeyEvent event);
		
		virtual void doMouseDown(MouseEvent event);
		virtual void doMouseUp(MouseEvent event);
		virtual void doMouseMove(MouseEvent event);
	
		virtual void doResize(Graphics& graphics);
};

#endif // __KEYEVENT_HPP
