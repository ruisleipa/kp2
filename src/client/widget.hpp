#ifndef __WIDGET_HPP
#define __WIDGET_HPP

#include "keyevent.hpp"
#include "mouseevent.hpp"
#include "vector2d.hpp"

class View;

class Widget
{
	public:
		void setPosition(Vector2D position);	
		Vector2D getPosition();
		
		void setSize(Vector2D size);	
		Vector2D getSize();
		
		Widget();
		virtual ~Widget();
		
		virtual void keyDown(KeyEvent event);
		virtual void keyUp(KeyEvent event);
		
		virtual void mouseDown(MouseEvent event);
		virtual void mouseUp(MouseEvent event);
		virtual void mouseMove(MouseEvent event);
		
		virtual void mouseOn();
		virtual void mouseOut();
		
		virtual void blur();
		virtual void focus();
		
		virtual void draw();

	
	protected:
		View* getParent();
	
	private:
		void setParent(View* view);
	
		Vector2D m_position;
		Vector2D m_size;

		View* m_parent;
		
		friend class View;
};

#endif // __WIDGET_HPP
