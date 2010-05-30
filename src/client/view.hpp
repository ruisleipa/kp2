#ifndef __VIEW_HPP
#define __VIEW_HPP

#include "eventlistener.hpp"
#include "widget.hpp"

#include <vector>

class View : public EventListener
{
	public:
		virtual void keyDown(KeyEvent event);
		virtual void keyUp(KeyEvent event);
		virtual void mouseDown(MouseEvent event);
		virtual void mouseUp(MouseEvent event);
		virtual void mouseMove(MouseEvent event);
		
		void draw();
		
		void addWidget(Widget* widget);
		
		virtual void calculateLayout();
		virtual void onActivate();
		
		View();
		View(const View&);
	
	private:
		Widget* findWidgetUnderPoint(Vector2D point);
		
		std::vector<Widget*> m_widgets;
		
		Widget* m_focused;
		Widget* m_mouse_over;
};

#endif

