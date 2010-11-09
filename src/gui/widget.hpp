#ifndef WIDGET_HPP
#define WIDGET_HPP

#include "graphics/vector2d.hpp"
#include "graphics/window.hpp"

#include "events/eventlistener.hpp"
#include "events/keyevent.hpp"
#include "events/mouseevent.hpp"
#include "events/drawevent.hpp"

#include "utils/noncopyable.hpp"

class Container;

class Widget: public EventListener, public NonCopyable
{
	public:
		void setPosition(Vector2D position);
		void setPixelPosition(Vector2D position);

		void setSize(Vector2D size);	
		void setPixelSize(Vector2D size);	
		
		void setVisible(bool visible);
		bool getVisible();

		virtual void handleEvent(Event* event);
		
		Container* getParent();
		
		Widget();
		virtual ~Widget();
	
	protected:	
		bool hasPixelPosition();
		Vector2D getPosition();
		
		bool hasPixelSize();
		Vector2D getSize();	
	
	private:
		void setParent(Container* container);
			
		bool visible;
			
		Container* parent;
	
		Vector2D position;
		bool pixelPosition;
		
		Vector2D size;
		bool pixelSize;		
		
		friend class Container;
};

#include "container.hpp"

#endif // WIDGET_HPP
