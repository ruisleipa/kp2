#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <vector>
#include <list>
#include "widget.hpp"

class Container : public Widget
{
	public:
		virtual void showOnlyWidget(const std::string& tag);
		
		Widget& getChildByName(const std::string& name);
		
		template<class T>
		T& getChildByName(const std::string& name)
		{
			Widget& widget = getChildByName(name);
			
			try
			{
				T& casted = dynamic_cast<T&>(widget);
				
				return casted;
			}
			catch(std::bad_cast)
			{
				std::stringstream ss;
				
				ss << "Widget named \"" << name;
				ss << "\" is of type \"";
				ss << demangleName(typeid(widget).name()) << "\", ";
				ss << "type \"" << demangleName(typeid(T).name()) << "\" expected.";
				
				throw std::runtime_error(ss.str());
			}
		}
		
		std::list<Widget*> getChildrenByName(const std::string& name);
		
		template<class T>
		std::list<T*> getChildrenByName(const std::string& name)
		{
			std::list<Widget*> list = getChildrenByName(name);
			std::list<T*> castedList;
			
			std::list<Widget*>::iterator i;
			
			for(i = list.begin(); i != list.end(); ++i)
			{
				T* casted = dynamic_cast<T*>(*i);
				
				if(casted)
					castedList.push_back(casted);
			}
			
			return castedList;
		}
		
		virtual void handleEvent(Event* event);
		
		void removeWidget(Widget& child);
		
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

