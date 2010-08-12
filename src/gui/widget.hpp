#ifndef WIDGET_HPP
#define WIDGET_HPP

#include "graphics/vector2d.hpp"
#include "graphics/window.hpp"

#include "events/eventlistener.hpp"
#include "events/keyevent.hpp"
#include "events/mouseevent.hpp"

#include "utils/noncopyable.hpp"

class Container;

class Widget: public EventListener, public NonCopyable
{
	public:
		void setPosition(Vector2D position);	
		Vector2D getPosition();
		
		Vector2D getAbsolutePosition();
		
		void setSize(Vector2D size);	
		Vector2D getSize();
		
		void setVisible(bool visible);
		bool getVisible();
		
		/*
		These are the functions for signaling that an event has
		happened.		
		*/		
		virtual void doKeyDown(KeyEvent event);
		virtual void doKeyUp(KeyEvent event);				
		
		virtual void doMouseDown(MouseEvent event);
		virtual void doMouseUp(MouseEvent event);
		virtual void doMouseMove(MouseEvent event);	
		
		virtual void doResize(Window& window);		
		
		virtual void doMouseOn();
		virtual void doMouseOut();		
		
		virtual void doBlur();
		virtual void doFocus();	
		
		virtual void doDraw(Window& window);		
		
		virtual void doShow();
		virtual void doHide();
		
		Container* getParent();
		
		Widget();
		virtual ~Widget();
	
	protected:		
		void setParent(Container* container);
		
		Window* getWindow();
		virtual void setWindow(Window* window);
		
		/*
		These are the functions that implement object specific handler
		for an event.
		*/		
		virtual void onKeyDown(KeyEvent event);
		virtual void onKeyUp(KeyEvent event);
		
		virtual void onMouseDown(MouseEvent event);
		virtual void onMouseUp(MouseEvent event);
		virtual void onMouseMove(MouseEvent event);
	
		virtual void onResize(Window& window);
		
		virtual void onMouseOn();
		virtual void onMouseOut();	
		
		virtual void onBlur();
		virtual void onFocus();	
		
		virtual void onDraw(Window& window);
		
		virtual void onShow();
		virtual void onHide();
	
	private:
		Vector2D position;
		Vector2D size;
		
		bool visible;
		
		Container* parent;
		Window* window;		
		
		friend class Container;
};

#include "container.hpp"

#endif // WIDGET_HPP
