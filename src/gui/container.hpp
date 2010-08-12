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
		
		void addWidget(Widget* widget);
		void addWidget(std::string tag,Widget* widget);
		
		Widget* getWidget(std::string tag);
		
		Container();
		Container(const Container&);
		
	protected:
		int getWidgetCount();
		Widget* getWidget(int index);
	
	private:
		Widget* findWidgetUnderPoint(Vector2D point);

		Widget* m_focused;
		Widget* m_mouse_over;

		class TaggedWidget
		{
			public:
				std::string m_tag;
				Widget* m_widget;
		};

		std::vector<TaggedWidget> m_widgets;
};

#endif // CONTAINER_HPP

