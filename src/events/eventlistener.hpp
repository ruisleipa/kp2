#ifndef EVENTLISTENER_HPP
#define EVENTLISTENER_HPP

class KeyEvent;
class MouseEvent;
//class Graphics;
class Connection;

class EventListener
{
	public:
		virtual void keyDown(KeyEvent event);
		virtual void keyUp(KeyEvent event);
		
		virtual void mouseDown(MouseEvent event);
		virtual void mouseUp(MouseEvent event);
		virtual void mouseMove(MouseEvent event);
	
		virtual void doConnectionEvent(Connection& connection);
};

#endif // KEYEVENT_HPP
