#ifndef WIDGET_HPP
#define WIDGET_HPP

#include "eventlistener.hpp"
#include "vector2d.hpp"
#include "keyevent.hpp"
#include "mouseevent.hpp"
#include "graphics.hpp"

class Widget: public EventListener
{
	public:
		void setPosition(Vector2D position);	
		Vector2D getPosition();
		Vector2D getScreenPosition();
		
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
		
		virtual void doResize(Graphics& graphics);		
		
		virtual void doMouseOn();
		virtual void doMouseOut();		
		
		virtual void doBlur();
		virtual void doFocus();	
		
		virtual void doDraw(Graphics& graphics);		
		
		virtual void doShow();
		virtual void doHide();
		
		virtual void doConnectionEvent(Connection& connection);
		
		
		Widget* getParent();
		
		Widget();
		virtual ~Widget();
	
	protected:		
		void setParent(Widget* view);
		
		Widget* getRootWidget(const std::string& tag);
		
		/*
		These are the functions that implement object specific handler
		for an event.
		*/		
		virtual void onKeyDown(KeyEvent event);
		virtual void onKeyUp(KeyEvent event);
		
		virtual void onMouseDown(MouseEvent event);
		virtual void onMouseUp(MouseEvent event);
		virtual void onMouseMove(MouseEvent event);
	
		virtual void onResize(Graphics& graphics);
		
		virtual void onMouseOn();
		virtual void onMouseOut();	
		
		virtual void onBlur();
		virtual void onFocus();	
		
		virtual void onDraw(Graphics& graphics);
		
		virtual void onShow();
		virtual void onHide();
		
		virtual void onConnectionEvent(Connection& connection);
	
	private:
		Vector2D m_position;
		Vector2D m_size;

		Widget* m_parent;
		
		bool m_visible;
		
		friend class Container;
};

#endif // WIDGET_HPP
