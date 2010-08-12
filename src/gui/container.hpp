#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <vector>
#include "widget.hpp"

class Container : public Widget
{
	public:
		virtual void doKeyDown(KeyEvent event);
		virtual void doKeyUp(KeyEvent event);
		virtual void doMouseDown(MouseEvent event);
		virtual void doMouseUp(MouseEvent event);
		virtual void doMouseMove(MouseEvent event);
				
		virtual void doResize(Window& window);
		virtual void doDraw(Window& window);
		
		void addChild(Widget* child);
		void addChild(std::string tag,Widget* child);
		
		Widget* getChild(std::string tag);
		
		Container();
		
	protected:
		int getChildCount();
		Widget* getChild(int index);
		
		virtual void setWindow(Window* window);
	
	private:
		void propagateWindowPointer();
	
		Widget* findWidgetUnderPoint(Vector2D point);

		Widget* focusedChild;
		Widget* mouseOverChild;

		class TaggedWidget
		{
			public:
				std::string tag;
				Widget* widget;
		};

		std::vector<TaggedWidget> children;
};

#endif // CONTAINER_HPP

