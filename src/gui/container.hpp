#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <vector>
#include "widget.hpp"

class Container : public Widget
{
	public:
		virtual void keyDown(KeyEvent event);
		virtual void keyUp(KeyEvent event);
		virtual void mouseDown(MouseEvent event);
		virtual void mouseUp(MouseEvent event);
		virtual void mouseMove(MouseEvent event);
		
		virtual void resize(Window& window);
		virtual void draw(Window& window);
		
		Container();
		
	protected:
		void addChild(Widget& child);
	
		int getChildCount();
		Widget* getChild(int index);
	
	private:
		Widget* findWidgetUnderPoint(Vector2D point);

		Widget* focusedChild;
		Widget* mouseOverChild;

		std::vector<Widget*> children;
};

#endif // CONTAINER_HPP

