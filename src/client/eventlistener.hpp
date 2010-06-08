#ifndef __EVENTLISTENER_HPP
#define __EVENTLISTENER_HPP

class KeyEvent;
class MouseEvent;
class Graphics;

class EventListener
{
	public:
		virtual void keyDown(KeyEvent event);
		virtual void keyUp(KeyEvent event);
		
		virtual void mouseDown(MouseEvent event);
		virtual void mouseUp(MouseEvent event);
		virtual void mouseMove(MouseEvent event);
	
		virtual void resize(Graphics& graphics);
};

#endif // __KEYEVENT_HPP
