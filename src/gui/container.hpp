#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <vector>
#include "widget.hpp"

class Container : public Widget
{
	public:
		virtual void showOnlyWidget(const std::string& tag);
		
		void addWidget(Widget& child);
		void addWidget(const std::string& tag,Widget& child);

		virtual void handleEvent(Event* event);
		
		virtual void resize(Window& window);
		
		Container();
		
	protected:	
		int getChildCount();
		Widget* getChild(int index);
		
		void handleKeyEvent(KeyEvent* event);
		void handleMouseDownEvent(MouseDownEvent* event);
		void handleMouseUpEvent(MouseUpEvent* event);
		void handleMouseMoveEvent(MouseMoveEvent* event);
		void handleDrawEvent(DrawEvent* event);
		
		Vector2D calculateWidgetPosition(Widget* widget,Vector2D ourSize);
		Vector2D calculateWidgetSize(Widget* widget,Vector2D ourSize);
		
		virtual Vector2D getWidgetPosition(Widget* widget,Vector2D ourSize);
		virtual Vector2D getWidgetSize(Widget* widget,Vector2D ourSize);
	
	private:
		Widget* findWidgetUnderMouse(MouseEvent* event);
		
		void convertAreaEventForChild(AreaEvent* event,Widget* widget);
				
		Widget* focusedChild;
		Widget* mouseOverChild;

		std::map<std::string,Widget*> tags;
		std::vector<Widget*> children;
		
		bool showBounds;
};

#endif // CONTAINER_HPP

