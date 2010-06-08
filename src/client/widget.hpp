#ifndef __WIDGET_HPP
#define __WIDGET_HPP

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
		
		void setSize(Vector2D size);	
		Vector2D getSize();
		
		void setVisible(bool visible);
		bool getVisible();
		
		virtual void mouseOn();
		virtual void mouseOut();
		
		virtual void blur();
		virtual void focus();
		
		virtual void draw(Graphics& graphics);
		
		virtual void onShow();
		virtual void onHide();
		
		Widget* getParent();
		
		Widget();
		virtual ~Widget();
	
	protected:		
		void setParent(Widget* view);
	
	private:
		Vector2D m_position;
		Vector2D m_size;

		Widget* m_parent;
		
		bool m_visible;
		
		friend class Container;
};

#endif // __WIDGET_HPP
