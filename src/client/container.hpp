#ifndef __CONTAINER_HPP
#define __CONTAINER_HPP

#include <vector>
#include "widget.hpp"
#include "fontcollection.hpp"

class Container : public Widget
{
	public:
		virtual void keyDown(KeyEvent event);
		virtual void keyUp(KeyEvent event);
		virtual void mouseDown(MouseEvent event);
		virtual void mouseUp(MouseEvent event);
		virtual void mouseMove(MouseEvent event);
				
		virtual void calculateLayout();
		virtual void onActivate();
		
		virtual void resize(Graphics& graphics);
		virtual void draw(Graphics& graphics);
		
		void addWidget(Widget* widget);
		void addWidget(std::string tag,Widget* widget);
		
		Widget* getWidget(std::string tag);
		
		Container();
		Container(const Container&);
	
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
		FontCollection m_font_collection;
};

#endif // __CONTAINER_HPP

