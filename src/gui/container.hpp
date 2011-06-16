#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <vector>
#include "widget.hpp"

class Container : public Widget
{
	public:
		virtual void showOnlyWidget(const std::string& tag);
		
		Widget& getChildByName(const std::string& name);
		
		virtual void handleEvent(Event* event);
		
		
		Container();
		
	protected:
		void addWidget(Widget* child);
		
		int getChildCount();
		Widget* getChild(int index);
		
		void handleKeyEvent(KeyEvent* event);
		void handleMouseDownEvent(MouseDownEvent* event);
		void handleMouseUpEvent(MouseUpEvent* event);
		void handleMouseOutEvent(MouseOutEvent* event);
		void handleBlurEvent(BlurEvent* event);
		void handleMouseMoveEvent(MouseMoveEvent* event);
		void handleDrawEvent(DrawEvent* event);
		
		virtual Vector2D getWidgetPosition(Widget* widget,Vector2D ourSize) = 0;
		virtual Vector2D getWidgetSize(Widget* widget,Vector2D ourSize) = 0;
	
	private:
		Widget* findWidgetUnderMouse(MouseEvent* event);
		
		void convertAreaEventForChild(AreaEvent* event,Widget* widget);
		
		Widget* focusedChild;
		Widget* mouseOverChild;

		std::vector<Widget*> children;
		
		bool showBounds;
};

#endif // CONTAINER_HPP

